vagrant up

for i in {1..6}
do
  SERVER_PORT=$((8080 + $i))
  ./cli localhost $SERVER_PORT $i >> resultados/cliente.txt &
done