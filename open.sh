#./bin/bash

echo "g++ -o practicaA practicaA.cpp"
g++ -std=c++11 -o practicaA practicaA.cpp
echo "executing program"
./practicaA < comparables > resultat
#echo "cleaning"
