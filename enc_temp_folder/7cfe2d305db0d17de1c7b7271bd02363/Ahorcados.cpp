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
	Hangman(string, int);
	void printWord();
	void printLives();
	void guessWordTry();
	void changeGoodLetters();
	void gameLoop();
	bool checkLetters(char);
};

bool Hangman::checkLetters(char _char) {
	for (auto it = previouslySubmittedLetters.begin(); it != previouslySubmittedLetters.end(); ++it) {
		if (*it == _char) return true;
	} 
	previouslySubmittedLetters.push_back(_char);
	return false;
}

Hangman::Hangman(string _hangManWord, int _lives) {
	lives = _lives;
	hangManWord = _hangManWord;
	for (int i = 0; i < hangManWord.size(); i++) secretWord.push_back('_');
}

void Hangman::changeGoodLetters() {
	for (vector<int>::iterator it = correctLetters.begin(); it != correctLetters.end(); ++it) {
		secretWord[*it] = hangManWord[*it];
	}
}

void Hangman::printLives() {
	cout << "Lives remaining: " << lives << endl;
}

void Hangman::guessWordTry() {
	correctLetters.clear();
	cout << "Enter a letter: ";
	cin >> letterGuessed;
	if (checkLetters(letterGuessed[0])) {
		cout << "Already entered! 1 life less";
	} else {
		for (int i = 0; i < hangManWord.size(); i++){
			if (letterGuessed[0] == hangManWord[i]) correctLetters.push_back(i);
		}
		if (correctLetters.size() > 0) {
			cout << "Correct!\n";
			changeGoodLetters();
		}
		else {
			lives--;
			cout << "Bad try! Sorry" << endl;
		}
	}
	
}

void Hangman::printWord() {
	printLives();
	for (auto it = secretWord.begin(); it != secretWord.end(); ++it) cout << *it;
	cout << endl;
}

void Hangman::gameLoop() {
	while (lives != 0) {
		guessWordTry();
		printWord();
	}
}

int main(){
	string secretWord;
	cout << "Write a secretWord (and just one secretWord) and do not tell the other player: ";
	cin >> secretWord;
	while (secretWord.size() < 6) {
		system("cls");
		cout << "Write a secretWord and do not tell the other player: "; 
		cin >> secretWord;
	}
	int lives;
	cout << "Enter number of lives: ";
	cin >> lives;
	
	Hangman firstTry(secretWord, lives);
	firstTry.gameLoop();
}

/*cout << "    ______" << endl;
	cout << "   |      |" << endl;
	cout << "   |      0" << endl;
	cout << "   |     /|\\" << endl;
	cout << "   |      |" << endl;
	cout << "   |     / \\" << endl;
	cout << "___|___" << endl;*/