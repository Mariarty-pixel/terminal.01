CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = terminal
SOURCES = main.cpp \
          terminal.cpp \
          entry.cpp \
          directory.cpp \
          file.cpp \
          singlelinefile.cpp \
          multilinefile.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Сборка программы
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Компиляция .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Полная пересборка
rebuild: clean $(TARGET)

# Запуск
run: $(TARGET)
	./$(TARGET)

# Для удобства проверки
all: $(TARGET)

.PHONY: clean rebuild run all