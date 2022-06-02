# ssh

  ### Túnel con dos saltos

  - Desde Enterprise:


  ```bash
z # Acceso a Enterprise:
  ssh <username>@192.168.1.70

  ssh -f -N -l sacta -L192.168.21.70:<PORT1>:<IP_PICT>:22 172.30.237.210
  ```

  (la última ip sirve la de cualquier máquina de los Strings de Torrejón a la que sí que se tenga acceso desde la máquina de desarrollo)

  - Desde la máquina de desarrollo:

  ```bash
  ssh -f -N -l `whoami` -L<PORT2>:192.168.21.70:<PORT1> 192.168.21.70

  # Cargar pirata en PICT remota:
  carga post tunnel PORT2 `whoami`
  ```

