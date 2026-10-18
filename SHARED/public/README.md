# Exemplo do PHP usando Shared Library em C

## Estrutura do projeto Web
```text
[SHARED]
[🐧🐘]> tree
.
├── dinamica
├── dinamica.go
├── dinamicago
├── dinamica.php
├── include
│   └── minha_lib.h
├── lib
│   └── libminha_lib.so
├── Makefile
├── programa
├── public
│   ├── index.php
│   └── README.md
└── src
    ├── dinamica.c
    ├── main.c
    └── minha_lib.c

5 directories, 13 files
[SHARED]

```
## Comandos no terminal estando na raiz do projeto.
```bash
php -d ffi.enable=true -S localhost:8080 -t public
```


