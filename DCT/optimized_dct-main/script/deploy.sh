#!/bin/bash

## Examples
# Send the file to your local vm
# ./script/deploy.sh mynetlinkid -vm "make arm ALGO=NEON" "./test/8x8_64_byte 8 8"

# Execute on remote ARM
# ./script/deploy.sh mynetlinkid -arm "make arm ALGO=NAIVE" "./test/8x16_128_byte 8 16" user1

netlink_id=$1
mode=$2 # -arm, -vm, -prof, -clean
make=$3 # make [arm] ALGO=NAIVE || UNOPTIMIZED || NEON
execution_args=$4 # e.g. "./test/8x8_64_byte 8 8"
arm_user=$5 # There are 4 users on the machine: user1, user2, user3, user4

root_dir=$( cd "$(dirname "${BASH_SOURCE[0]}")" || exit ; cd ../; pwd -P ) # https://stackoverflow.com/questions/24112727/relative-paths-based-on-file-location-instead-of-current-working-directory
arm_password="q6coHjd7P"

# Execute commands on local from root directory of repo
cd "$root_dir" || exit;
echo;

# Clean folder on remmote
if [[ "$mode" == "-clean" ]]; then
  echo "Deleting folder /tmp/${netlink_id}/ on remote";
  ssh "$netlink_id"@seng440.ece.uvic.ca "cd /tmp; rm -r ./${netlink_id}";
  echo;
  exit 0;
fi

# ssh into remote and make a folder in /tmp
echo "Creating folder /tmp/${netlink_id}/ on remote";
ssh "$netlink_id"@seng440.ece.uvic.ca "cd /tmp; mkdir -p ${netlink_id}";
echo;

# Send local source code to remote
echo "Sending local source code to remote /tmp/${netlink_id}/ @ seng440.ece.uvic.ca";
scp -r ./src ./include ./test Makefile "$netlink_id"@seng440.ece.uvic.ca:/tmp/"$netlink_id";
echo;

## Commands to be executed on remote
# Compile remote source code
commands=()
commands+="echo;"
commands+="echo 'Compile on remote';"
commands+="cd /tmp/${netlink_id};"
commands+="${make};"
commands+="chmod 777 ./dct.exe;"
commands+="echo;"

# Run on ARM machine
if [[ "$mode" == "-arm" ]]; then
  # Transfer executable and test files to ARM machine
  commands+="echo 'Transfer files to ARM';"
  commands+="lftp -c \"open -u ${arm_user},${arm_password} ${arm_user}@arm;\
    mkdir -p ${netlink_id}/test;\
    put -O ${netlink_id} dct.exe;\
    mirror -R test ${netlink_id}/test\";"
  commands+="echo;"

  # Execute on ARM machine
  commands+="echo 'Execute on ARM';"
  commands+="eval \"{ sleep 1; echo ${arm_user};\
    sleep 1; echo ${arm_password};\
    echo 'cd ${netlink_id}';\
    echo 'chmod 777 dct.exe';\
    echo './dct.exe ${execution_args}';\
    sleep 1; }\"\
    | telnet arm;"
  commands+="echo;"

  # Clean
  commands+="echo 'Clean up after deploy and execution';"
  commands+="cd ..;"
  commands+="rm -rf ${netlink_id};"

  commands+="eval \"{ sleep 1;\
    echo ${arm_user};\
    sleep 1;\
    echo ${arm_password};\
    sleep 1;\
    echo 'rmdir ${netlink_id}';\
    sleep 1; }\"\
    | telnet arm;"
  commands+="echo;"
fi

# ssh into remote
echo "ssh into remote @ seng440.ece.uvic.ca and execute commands";
ssh -t "$netlink_id"@seng440.ece.uvic.ca "$commands";
echo;

# Run on local vm
if [[ "$mode" == "-vm" ]]; then
  echo "Download dct.exe from remote @ seng440.ece.uvic.ca to local";
  scp "$netlink_id"@seng440.ece.uvic.ca:/tmp/"$netlink_id"/*.exe "$root_dir";
  echo;

  echo "Send *.exe and test files to vm"; # You don't have to place files on vm to execute
  scp -P 5555 -r ./*.exe ./test root@localhost:~;
  echo "Files have been placed in vm";
  echo;

  qemu-arm ./dct.exe ${execution_args};
fi

# Download assembly output to local
if [[ "$mode" == "-prof" ]]; then
  echo "Download assembly files from remote @ seng440.ece.uvic.ca to local";
  scp "$netlink_id"@seng440.ece.uvic.ca:/tmp/"$netlink_id"/*.s "$root_dir";
  echo;
fi
