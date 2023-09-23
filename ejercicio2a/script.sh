# Get updated urls/packages sources? & tools
apt-get update

# Get several software packages
apt-get install -y net-tools debconf-utils libc-dev-bin gcc

# The alias for ls
grep -q "alias ls='ls -la'" /home/vagrant/.bashrc || echo -e "\\nalias ls='ls -la'" >> /home/vagrant/.bashrc

SERVER_IP="192.168.56.100"
for i in {1..6}
do
  SERVER_PORT=$((8080 + $i))

  if [ "$(hostname)" = "vm1" ]; then
    gcc server.c -o server -lm
    ./server $SERVER_PORT $i >> ./resultados/server.txt &
  else
    gcc client.c -o client -lm
    ./client $SERVER_IP $SERVER_PORT $i >> ./resultados/client.txt
  fi
done