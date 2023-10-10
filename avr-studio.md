## Microchip Studio for AVR

Skonfigurowany projekt dla Microchip Studio znajduje się w folderze **template-ms**, jednak konieczna jest ustawienie prędkości pracy mikrokontrolera, gdyż jest ona ściśle związana z konfiguracją sprzętową _(fuse-bity / rezonator kwarcowy)_.

![fcpu](./images/fcpu.png)

Aby pracować z programatorem **USB/ASP** trzeba dodać urządzenie zewnętrzne, ponieważ ten programator nie jest oficjalnie wspierany.

![add-external-tool](./images/usbasp1.png)

W polu `Command` należy wybrać ścieżkę do `avrdude.exe`

W polu `Arguments` należy wpisać

```
-c usbasp -p m328p -U flash:w:$(TargetDir)$(TargetName).hex:i
```

![toolbar](./images/usbasp2.png)

Na pasku narzędzi powinno pojawić się `USBasp Atmega328P`

Jak po z**build**owaniu program się nie wgrywa, trzeba przeinstalować sterowniki programatora

![zadig](./images/usbasp3.png)