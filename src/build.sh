echo "[Compiling]"
g++ main.cpp -o ../build/output -lSDL2 -lSDL2_image -lSDL2_ttf

echo "[Running]"
../build/output
