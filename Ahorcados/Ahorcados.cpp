#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Hangman {
private:
	string hangManWord;
	string letterGuessed;
	vector<char> secretWord, previouslySubmittedLetters;
	vector<int> correctLetters;
	int lives = 7;
public:
	Hangman(string);
	void printWord();
	void printLives();
	void guessWordTry();
	void changeGoodLetters();
	void gameLoop();
	bool checkLetters(char);
	bool checkEndgame();
};

bool Hangman::checkLetters(char _char) {
	for (auto it = previouslySubmittedLetters.begin(); it != previouslySubmittedLetters.end(); ++it) {
		if (*it == _char) return true;
	} 
	previouslySubmittedLetters.push_back(_char);
	return false;
}

Hangman::Hangman(string _hangManWord) {
	hangManWord = _hangManWord;
	for (int i = 0; i < hangManWord.size(); i++) secretWord.push_back('_');
}

void Hangman::changeGoodLetters() {
	for (vector<int>::iterator it = correctLetters.begin(); it != correctLetters.end(); ++it) {
		secretWord[*it] = hangManWord[*it];
	}
}

void Hangman::printLives() {
	cout << "Vidas: ";
	for (int i = 0; i < lives; i++) {
		cout << "0 ";
	}
	cout << endl;
}

void Hangman::guessWordTry() {
	correctLetters.clear();
	cout << "Ingrese una letra: ";
	cin >> letterGuessed;
	if (checkLetters(letterGuessed[0])) {
		cout << "Ya pusiste esa letra! 1 vida menos" << endl;
		lives--;
	} else {
		for (int i = 0; i < hangManWord.size(); i++){
			if (letterGuessed[0] == hangManWord[i]) correctLetters.push_back(i);
		}
		if (correctLetters.size() > 0) {
			cout << "Correcto!\n";
			changeGoodLetters();
		}
		else {
			lives--;
			cout << "Mal intento! Perdon" << endl;
		}
	}
	
}

void Hangman::printWord() {
	printLives();
	for (auto it = secretWord.begin(); it != secretWord.end(); ++it) cout << *it;
	cout << endl;
}

bool Hangman::checkEndgame() {
	for (auto it = secretWord.begin(); it != secretWord.end(); ++it) {
		if (*it == '_') return true;
	}
	return false;
}

void Hangman::gameLoop() {
	while (lives != 0 && checkEndgame()) {
		guessWordTry();
		printWord();
	}
	if (lives == 0) cout << "PERDISTE! :(";
	else cout << "GANASTE!!";

}

int main(){
	string secretWord;
	cout << "Escribe una palabra secreta (y no le digas al otro jugador) de mas de 6 letras: ";
	cin >> secretWord;
	while (secretWord.size() < 6) {
		system("cls");
		cout << "Escribe una palabra secreta (y no le digas al otro jugador): "; 
		cin >> secretWord;
	}
	system("cls");
	Hangman firstTry(secretWord);
	firstTry.gameLoop();
}

