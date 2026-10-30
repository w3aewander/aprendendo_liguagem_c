# Cálculo Matemático com Pontos
>
> Wanderlei Silva do Carmo
> Eng. Arquiteto de Software
>

### O código fonte deve ser compilado com o comando abaixo

```bash
g++ -o distancia main.cpp -fPIC -lm

```

```Text

-fPIC: Código Independente de Posição
-lm: usar a biblioteca matemática (math.h)

No futuro vamos usar bibliotecas compartilhadas (shared objects) por isso o -fPIC.

```

## A biblioteca compartilhada foi compilada assim
```bash
g++ -fPIC -shared somatorio_dobros.cpp  -o libsomatorio_dobros.so
```
## Depois somatorio_dobro_teste.cpp foi compilado assim
```bash
g++ somatorio_dobros_teste.cpp -lsomatorio_dobros -L./  -o calcula_dobros
```

## Se for necessário ajuste o ambiente assim
```bash
LD_LIBRARY_PATH=.

```

## Execute assim:

```bash
 ./calcula_dobros
```