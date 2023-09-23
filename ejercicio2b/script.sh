# Get updated urls/packages sources? & tools
apt-get update

# Get several software packages
apt-get install -y net-tools debconf-utils libc-dev-bin gcc

# The alias for ls
grep -q "alias ls='ls -la'" /home/vagrant/.bashrc || echo -e "\\nalias ls='ls -la'" >> /home/vagrant/.bashrc

for i in {4..9}
do
  SERVER_PORT=$((8080 + $i))
  gcc server.c -o server -lm
  ./server $SERVER_PORT $i >> resultados.txt &
done