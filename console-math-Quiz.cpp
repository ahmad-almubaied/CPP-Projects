#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };
enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };

struct stQuestion {
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int UserAnswer = 0;
    bool AnswerResult = false;
};

struct stQuize {
    stQuestion QuestionList[100]; // مصفوفة عادية بدلاً من vector
    short NumberOfQuestions = 0;
    enOperationType OpType;
    enQuestionLevel QuestionLevel;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool isPass = false;
};

int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

short ReadHowManyQuestions() {
    short Number;
    do {
        cout << "How Many Questions do you want to answer? (1 to 100): ";
        cin >> Number;
    } while (Number < 1 || Number > 100);
    return Number;
}

enOperationType ReadOpType() {
    short OpType;
    do {
        cout << "Enter Operation Type [1]:Add, [2]:Sub, [3]:Mult, [4]:Div, [5]:Mix? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);
    return (enOperationType)OpType;
}

enQuestionLevel ReadQuestionLevel() {
    short Level;
    do {
        cout << "Enter Question Level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix? ";
        cin >> Level;
    } while (Level < 1 || Level > 4);
    return (enQuestionLevel)Level;
}

string GetOpSymbol(enOperationType OpType) {
    switch (OpType) {
    case Add: return "+";
    case Sub: return "-";
    case Mult: return "x";
    case Div: return "/";
    default:  return "Mix";
    }
}

string GetLevelText(enQuestionLevel Level) {
    switch (Level) {
    case Easy: return "Easy";
    case Med: return "Med";
    case Hard: return "Hard";
    case MixLevel: return "Mix";
    default: return "Mix";
    }
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType) {
    switch (OpType) {
    case Add: return Number1 + Number2;
    case Sub: return Number1 - Number2;
    case Mult: return Number1 * Number2;
    case Div: return Number1 / Number2;
    default: return Number1 + Number2;
    }
}

stQuestion GenerateQuestion(enOperationType OpType, enQuestionLevel QuestionLevel) {
    stQuestion Question;

    // تحديد مستوى الصعوبة الفعلي إذا كان الخيار مختلطاً
    enQuestionLevel ActualLevel = QuestionLevel;
    if (QuestionLevel == MixLevel) {
        ActualLevel = (enQuestionLevel)RandomNumber(1, 3);
    }

    // توليد الأرقام بناءً على مستوى الصعوبة
    switch (ActualLevel) {
    case Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }

    Question.QuestionLevel = ActualLevel;

    // تحديد نوع العملية الحسابية
    if (OpType == MixOp) {
        Question.OperationType = (enOperationType)RandomNumber(1, 4);
    }
    else {
        Question.OperationType = OpType;
    }

    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
    return Question;
}

void SetScreenColor(bool Right) {
    if (Right) {
        system("color 2F"); // أخضر
    }
    else {
        cout << "\a";       // جرس الإنذار
        system("color 4F"); // أحمر
    }
}

void ResetScreen() {
    system("cls");
    system("color 0F"); // العودة للوضع الافتراضي
}

void AskAndCorrectQuestion(stQuize& Quize, short QuestionNumber) {
    cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quize.NumberOfQuestions << "]\n\n";
    cout << Quize.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quize.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpSymbol(Quize.QuestionList[QuestionNumber].OperationType) << "\n";
    cout << "_________" << endl;

    cin >> Quize.QuestionList[QuestionNumber].UserAnswer;

    if (Quize.QuestionList[QuestionNumber].UserAnswer == Quize.QuestionList[QuestionNumber].CorrectAnswer) {
        Quize.QuestionList[QuestionNumber].AnswerResult = true;
        Quize.NumberOfRightAnswers++;
        cout << "\nRight Answer :-) \n";
        SetScreenColor(true);
    }
    else {
        Quize.QuestionList[QuestionNumber].AnswerResult = false;
        Quize.NumberOfWrongAnswers++;
        cout << "\nWrong Answer :-( \n";
        cout << "The right answer is: " << Quize.QuestionList[QuestionNumber].CorrectAnswer << "\n";
        SetScreenColor(false);
    }
}

void PrintQuizeResults(stQuize Quize) {
    ResetScreen();
    cout << "\n______________________________\n\n";
    cout << " Final Results is " << (Quize.NumberOfRightAnswers >= Quize.NumberOfWrongAnswers ? "PASS :-)" : "FAIL :-(") << "\n";
    cout << "______________________________\n\n";
    cout << "Number of Questions: " << Quize.NumberOfQuestions << endl;
    cout << "Questions Level    : " << GetLevelText(Quize.QuestionLevel) << endl;
    cout << "Operation Type     : " << GetOpSymbol(Quize.OpType) << endl;
    cout << "Right Answers      : " << Quize.NumberOfRightAnswers << endl;
    cout << "Wrong Answers      : " << Quize.NumberOfWrongAnswers << endl;
    cout << "______________________________\n\n";
}

void PlayMathGame() {
    stQuize Quize;
    Quize.NumberOfQuestions = ReadHowManyQuestions();
    Quize.QuestionLevel = ReadQuestionLevel();
    Quize.OpType = ReadOpType();
    for (short i = 0; i < Quize.NumberOfQuestions; i++) {
        // الإسناد المباشر للمصفوفة العادية
        Quize.QuestionList[i] = GenerateQuestion(Quize.OpType, Quize.QuestionLevel);
        AskAndCorrectQuestion(Quize, i);
    }
    PrintQuizeResults(Quize);
}

void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        PlayMathGame();
        cout << "\nDo you want to play again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
