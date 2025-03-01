#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

// Класс кольцевой очереди
template <typename T>
class CircularQueue {
private:
    int size;
    int front, rear;
    T* arr;

public:
    CircularQueue(int n) : size(n), front(0), rear(0) {
        arr = new T[size];
    }

    ~CircularQueue() {
        delete[] arr;
    }

    // Добавление элемента в очередь
    void enqueue(T value) {
        arr[rear] = value;
        rear = (rear + 1) % size;
    }

    // Извлечение элемента из очереди
    T dequeue() {
        T value = arr[front];
        front = (front + 1) % size;
        return value;
    }

    // Получение текущего элемента в очереди (не удаляя)
    T frontValue() {
        return arr[front];
    }

    // Проверка на пустоту
    bool isEmpty() {
        return front == rear;
    }

    // Заполнение очереди случайными значениями
    void fillQueue() {
        for (int i = 0; i < size; i++) {
            enqueue(rand() % 5); // Генерируем случайные числа от 0 до 4
        }
    }

    // "Крутить" очередь, т.е. делать один поворот
    void rotate() {
        enqueue(dequeue()); // Перемещаем первый элемент в конец
    }
};

// Класс для автоматической игры "Одинорукый бандит"
class SlotMachine {
private:
    CircularQueue<int> reel1, reel2, reel3;  // Три кольцевые очереди

public:
    SlotMachine() : reel1(5), reel2(5), reel3(5) {
        // Заполняем очереди случайными значениями
        reel1.fillQueue();
        reel2.fillQueue();
        reel3.fillQueue();
    }

    // Метод для спина барабанов
    void spinReels() {
        int spinCount = rand() % 10 + 5; // Сколько раз "крутить" барабаны (от 5 до 15)
        for (int i = 0; i < spinCount; i++) {
            reel1.rotate();
            reel2.rotate();
            reel3.rotate();
        }
    }

    // Метод для отображения результатов барабанов
    void displayReels() {
        cout << "Spin result: [ " << reel1.frontValue() << " | "
             << reel2.frontValue() << " | " << reel3.frontValue() << " ]" << endl;
    }

    // Метод для проверки выигрыша
    int checkWin() {
        int r1 = reel1.frontValue();
        int r2 = reel2.frontValue();
        int r3 = reel3.frontValue();

        if (r1 == r2 && r2 == r3) {
            if (r1 == 0) {
                cout << "Jackpot! All zeros! You won 1000 points!" << endl;
                return 1000;
            } else {
                cout << "Three of a kind! You won 500 points!" << endl;
                return 500;
            }
        } else if (r1 == r2 || r2 == r3 || r1 == r3) {
            cout << "Two of a kind! You won 100 points!" << endl;
            return 100;
        } else {
            cout << "No win, try again!" << endl;
            return 0;
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    SlotMachine slotMachine;
    char input;
    int totalScore = 0;

    cout << "Welcome to the \"Odnorukiy Bandit\" game!" << endl;
    cout << "Press Enter to spin or 'q' to quit." << endl;

    while (true) {
        cout << "Press Enter to spin or 'q' to quit: ";
        input = cin.get();
        if (input == 'q') break;

        slotMachine.spinReels();
        slotMachine.displayReels();

        totalScore += slotMachine.checkWin();
        cout << "Your current score: " << totalScore << " points" << endl << endl;

        cin.ignore();  // Ожидаем нажатие Enter
    }

    cout << "Thanks for playing! Your final score: " << totalScore << " points." << endl;
    return 0;
}
