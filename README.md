# dxlAPRS_encrypt

dxlAPRS_encrypt send a report zo wettersonde.net

## Install the required dependencies :

```
sudo apt-get install libcurl4-openssl-dev
```

### Unpack and compile :

```
  git clone https://github.com/DO2JMG/dxlAPRS_encrypt.git
  cd dxlAPRS_encrypt
  mkdir build
  cd build
  cmake ..
  make
```

### Add a cronjob :

Replace <ENCRYPT-FILENAME> and <YOUR-CALLSIGN> with your data, in the example they are just placeholders

```
  */1 * * * *  /home/pi/encrypt -f <ENCRYPT-FILENAME> -c <YOUR-CALLSIGN>
```

### Changing parameters for sondemod :

Replace <ENCRYPT-FILENAME> with your data, in the example they are just placeholders

```
-X <ENCRYPT-FILENAME>
```
