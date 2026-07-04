CC = gcc
CFLAGS = -Wall -Wextra -std=c17 # -Wall é pra alguns avisos na compilação, -Wextra é pra detalhes sobre a compilação e alguns avisos e recomendações.
# LDFLAGS =
TARGET = graph

SRC_DIR = .
BASE_DIR = Base
SEARCH_DIR = Algoritmos_de_Busca
EXTRA_DIR = Algoritmos_Extras

SOURCES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/utils.c \
	$(BASE_DIR)/adjacentListGraph.c \
	$(BASE_DIR)/adjacentMatrizGraph.c \
	$(SEARCH_DIR)/dfs.c \
	$(SEARCH_DIR)/bfs.c \
	$(EXTRA_DIR)/fleury.c \
	$(EXTRA_DIR)/tarjan_for_articulation.c \
	$(EXTRA_DIR)/planar.c 

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
