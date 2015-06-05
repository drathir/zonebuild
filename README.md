# zonebuild

* Generate DNS zones from dn42 registry files

## Installation
* Prepare:

  ```sh
  apt-get update
  apt-get install bind9
  cd /etc/bind
  ```
* Clone:

  ```sh
  git clone git://github.com/nixnodes/zonebuild.git
  ```
  
* Compile and install zbuild:

 ```sh
 cd zonebuild
 make clean
 ./configure
 sudo make install
 ```
 
* Configure:
  
  `vi scripts/config.user`

  -
 
  ```
  REGISTRY_BASE_PATH=/etc/bind
  REGISTRY_PATH=${REGISTRY_BASE_PATH}/net.dn42.registry/data
  OUT_PATH=/etc/bind
  ```

  * Data is written in `$OUT_PATH/<tier[0-2]|res|ipv6>/`
  * Registry repo will be created in `$REGISTRY_BASE_PATH`
  
  -

  ```
  SERVER_NAME_TIER0=<a-z>.root-servers.dn42
  SERVER_NAME_TIER1=<a-z>.zone-servers.dn42
  SERVER_NAME_TIER2=<a-z>.dn42-servers.dn42
  ```
  
  * Select a free letter and enter the proper glue record into each respective zone: https://io.nixnodes.net/?q=zone-servers|dn42-servers|root-servers
  
  -
  
  Default settings are stored in`scripts/config`, all changes should be put in `scripts/config.user`


  