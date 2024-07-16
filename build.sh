echo "Starting Schrandomizer build UwU ..."

rm schrandomized.json
clear
gcc -I include cJSON.c schrandomizer.c -o schrandomizer
chmod +x schrandomizer
./schrandomizer

echo "Compiled and chmodded, we schroiting! >w<"
