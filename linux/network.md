# Network

### Configure static ip address

1. ip link: get interface name
2. Create a file on /etc/systemd/network/<interface>.network

```  
[Match]
Name=<interface>

[Network]
Address=<Desired ip>/24
Gateway=192.168.1.1
DNS=8.8.8.8
DNS=8.8.4.4
```
  
3. Ensure dhcpd service is off

```sh
sudo systemctl disable dhcpcd.service
```

```sh
sudo systemctl stop dhcpcd.service
```

4. Enable and start systemd-networkd service

```sh
sudo systemctl enable systemd-networkd
```

```sh
sudo systemctl start systemd-networkd
```
