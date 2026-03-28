#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;

enum enLevels { easy = 1, med = 2, hard = 3, mix = 4 };

enum enOprts { add = 1, sub = 2, mul, Div = 4, Mix };

struct stQuestionInfo
{
	short number1 = 0;
	short number2 = 0;
	enLevels questionLevel;
	enOprts questionOprt;
	short userAnswer = 0;
	short correctAnswer = 0;
	bool isAnswerCorrect;
};

struct stQuizInfo
{
	stQuestionInfo questionList[100];
	short numberOfQuestions;
	short numberOfRightAnswers = 0;
	short numberOfWrongAnswers = 0;
	enLevels quizLevel;
	enOprts quizOprt;
	bool isPass;
};

short randomNumber(short from, short to)
{
	short randomNumber = 0;
	randomNumber = rand() % (to - from + 1) + from;
	return randomNumber;
}

void resetScreen()
{
	system("cls");
	system("color 0F");
}

short getNumberOfQuestions()
{
	short numberOfQuestions = 0;

	do
	{
		cout << "How Many Questions You Want To Answer ? [MAX 100!]\n";
		cin >> numberOfQuestions;
	} while (numberOfQuestions < 1 || numberOfQuestions > 100);

	return numberOfQuestions;
}

enLevels getQuizLevel()
{
	short questionsLevel;

	do
	{
		cout << "Please Enter Questions Level: [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ?\n";
		cin >> questionsLevel;
	} while (questionsLevel > 4 || questionsLevel < 1);

	return enLevels(questionsLevel);
}

enOprts getOperationType()
{
	short operationType = 0;

	do
	{
		cout << "Please Enter Operation Type: [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix ?\n";
		cin >> operationType;
	} while (operationType > 5 || operationType < 1);

	return enOprts(operationType);
}

short calculate(short num1, short num2, enOprts oprtType)
{
	switch (oprtType)
	{
	case enOprts::add:
		return num1 + num2;
	case enOprts::mul:
		return num1 * num2;
	case enOprts::Div:
		return num1 / num2;
	case enOprts::sub:
		return num1 - num2;
	}
}

stQuestionInfo generateQuestion(enLevels quizLevel, enOprts quizOprt)
{
	stQuestionInfo questionInfo;

	if (quizLevel == enLevels::mix)
		quizLevel = enLevels(randomNumber(1, 3));

	if (quizOprt == enOprts::Mix)
		quizOprt = enOprts(randomNumber(1, 4));

	questionInfo.questionLevel = quizLevel;
	questionInfo.questionOprt = quizOprt;

	switch (quizLevel)
	{
	case enLevels::easy:
		questionInfo.number1 = randomNumber(1, 10);
		questionInfo.number2 = randomNumber(1, 10);
		break;
	case enLevels::med:
		questionInfo.number1 = randomNumber(10, 50);
		questionInfo.number2 = randomNumber(10, 50);
		break;
	case enLevels::hard:
		questionInfo.number1 = randomNumber(50, 100);
		questionInfo.number2 = randomNumber(50, 100);
		break;
	}

	questionInfo.correctAnswer = calculate(questionInfo.number1, questionInfo.number2, questionInfo.questionOprt);
	return questionInfo;
}

void generateQuiz(stQuizInfo& quizInfo)
{
	for (short question = 0; question < quizInfo.numberOfQuestions; question++)
		quizInfo.questionList[question] = generateQuestion(quizInfo.quizLevel, quizInfo.quizOprt);
}

char getSymbol(enOprts oprt)
{
	switch (oprt)
	{
	case enOprts::add:
		return '+';
	case enOprts::sub:
		return '-';
	case enOprts::mul:
		return 'x';
	case enOprts::Div:
		return '/';
	}
}

void SetScreenColor(bool result)
{
	if (result)
		system("color 2F");
	else
	{
		cout << "\a";
		system("color 4F");
	}
}

void printTheQuestion(stQuizInfo quizInfo, short question)
{
	cout << "\n\nQuestion [" << question + 1 << "/" << quizInfo.numberOfQuestions << "]\n\n";
	cout << quizInfo.questionList[question].number1 << " ";
	cout << getSymbol(quizInfo.questionList[question].questionOprt) << " ";
	cout << quizInfo.questionList[question].number2 << " = ?";
	cout << "\n--------------\n";
}

short getQuestionAnswer()
{
	short answer = 0;
	cin >> answer;
	return answer;
}

void correctAnswer(stQuizInfo& quizInfo, short question)
{
	if (quizInfo.questionList[question].correctAnswer == quizInfo.questionList[question].userAnswer)
	{
		cout << "\n\nRight Answer :-)\n";
		quizInfo.numberOfRightAnswers++;
		quizInfo.questionList[question].isAnswerCorrect = true;
	}
	else
	{
		cout << "\n\nWrong Answer :-(\n";
		cout << "The Correct Answer: " << quizInfo.questionList[question].correctAnswer << endl;
		quizInfo.questionList[question].isAnswerCorrect = false;
		quizInfo.numberOfWrongAnswers++;
	}

	SetScreenColor(quizInfo.questionList[question].isAnswerCorrect);
}

void askAndCorrect(stQuizInfo& quizInfo)
{
	for (short question = 0; question < quizInfo.numberOfQuestions; question++)
	{
		printTheQuestion(quizInfo, question);
		quizInfo.questionList[question].userAnswer = getQuestionAnswer();
		correctAnswer(quizInfo, question);
	}

	quizInfo.isPass = (quizInfo.numberOfRightAnswers >= quizInfo.numberOfWrongAnswers);
}

string tabs(short numberOfTabs)
{
	string tabs = "";

	for (short i = 1; i <= numberOfTabs; i++)
		tabs += '\t';

	return tabs;
}

string showIsPass(bool isPass)
{
	SetScreenColor(isPass);
	if (isPass)
		return "Pass";
	else
		return "Fail";
}

string showOprtType(enOprts oprtType)
{
	string oprts[]{ "Add", "Sub", "Mul", "Div", "Mix" };

	return oprts[oprtType - 1];
}

string showLevel(enLevels level)
{
	string levels[]{ "Easy", "Med", "Hard", "Mix" };

	return levels[level - 1];
}

void printFinalResult(stQuizInfo quizInfo)
{
	cout << tabs(4) << "----------------------------------\n";
	cout << tabs(4) << "       Final Result Is " << showIsPass(quizInfo.isPass) << endl;
	cout << tabs(4) << "----------------------------------\n";
	cout << tabs(4) << "Number Of Rounds: " << quizInfo.numberOfQuestions << "\n";
	cout << tabs(4) << "Questions Level: " << showLevel(quizInfo.quizLevel) << "\n";
	cout << tabs(4) << "Operation Type: " << showOprtType(quizInfo.quizOprt) << "\n";
	cout << tabs(4) << "Number Of Right Answers: " << quizInfo.numberOfRightAnswers << "\n";
	cout << tabs(4) << "Number Of Wrong Answers: " << quizInfo.numberOfWrongAnswers << "\n";
	cout << tabs(4) << "----------------------------------\n";
}

void playGame()
{
	stQuizInfo quizInfo;

	quizInfo.numberOfQuestions = getNumberOfQuestions();
	quizInfo.quizLevel = getQuizLevel();
	quizInfo.quizOprt = getOperationType();

	generateQuiz(quizInfo);
	askAndCorrect(quizInfo);
	printFinalResult(quizInfo);
}

void startQuiz()
{
	char playAgain = 'y';

	do
	{
		resetScreen();
		playGame();
		cout << tabs(4) << "Do You Want To Play Again ? [Y/N]? ";
		cin >> playAgain;
	} while (playAgain == 'y' || playAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));
	startQuiz();
	return 0;
}