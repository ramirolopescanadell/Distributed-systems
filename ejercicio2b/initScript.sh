gcc client3.c -lm -o cli
vagrant up

for i in {4..9}
do
  SERVER_PORT=$((8080 + $i))
  SERVER_IP="192.168.0.200"
  ./cli $SERVER_IP $SERVER_PORT $i >> resultados/cliente.txt
done