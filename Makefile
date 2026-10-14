# 1. Variáveis de configuração
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = wsmap

# 2. Alvo principal (o que o comando 'make' vai rodar por padrão)
all: $(TARGET)

# 3. Regra para gerar o executável a partir do código-fonte
$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET)

# 4. Regra para limpar os arquivos gerados
clean:
	rm -f $(TARGET)
