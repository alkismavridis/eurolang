rm ../data/pr_gcc
rm ../data/pr_ld

../out/eulc ../data/test.eul ../data/hello
ld ../data/hello -e _startEul -o ../data/pr_ld
gcc -no-pie -o ../data/pr_gcc ../data/hello
