




Przykładowa struktura projektu

- `hardware/` - schmat naszego urządzenia. Można wykorzystać **Eagle**/**Kicad** lub inny program do projektowania PCB.
- `firmware/` - program wgrywany do mikrokontrolera
- `readme.md.` - dokumentacja projektu

Dokumentację 



# hardware

- schmat **Eagle**/**Kicad**
- wyeksportować do `pdf`

# Projekt jajssajsajd

- urzadzenie wejściowe + wejściowe

## Etap 1

- Temat projektu
- Opis
- Lista elementów

[link](www.google.pl)
![img](./img.png)

Fragment kodu

```cpp
_delay_ms(100);
PORTD |= (1 << 0);
_delay_ms(100);
PORTD &= ~(1 << 0);
```