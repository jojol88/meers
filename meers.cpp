#include <iostream>
#include <vector>
#include <memory>


template <typename T>
inline void callWithMax(const T& a, const T& b)
{
	f(a > b ? a : b);
}


{
   std::vector<int> vec;
   const std::vector<int>::iterator iter = vec.begin();
   *iter = 10;
   ++iter; // error


   std::vector<int>::const_iterator citer = vec.begin();
   *citer = 10; // error
   ++citer;
}

/**********************************************************************************************/

class FileSystem // из вашей библиотеки
{
public:
   FileSystem() {}
   ~FileSystem() {}

   std::size_t numDisks() const {}
   FileSystem& tfs();

};

FileSystem & FileSystem::tfs()
{
   static FileSystem fs;

   return fs;
}

class Directory // создан пользователем
{
public:
   Directory() {}
   Directory(params);
   ~Directory() {}

   Directory& tempDir(); // каталог для временных файлов

};

Directory::Directory(params)
{
   std::size_t disks = tfs().numDisks();
}

Directory & Directory::tempDir()
{
   static Directory id;

   return id;
}

/*********************************************************************************************/

class Uncopyable
{
protected:
   Uncopyable();
   ~Uncopyable();

private:
   Uncopyable(const Uncopyable&);            // предотвратить копирование объектов
   Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale : private Uncopyable
{
};

/**********************************************************************************************/

class Widget
{
public:
   Widget() {}
   ~Widget() {}

   Widget& operator=(const Widget& rhs)
   {
      if (this == &rhs) return *this;
      /*...*/
      return *this; // вернуть объект из левой части выражения
   }
};


Widget& Widget::operator=(const Widget& rhs)
{
   Bitmap *pOrig = pb;
   pb = new Bitmap(*rhs.pb);
   delete pOrig;

   return *this; // вернуть объект из левой части выражения
}

/*********************************************************************************************/

void logCall(const std::string& funcName);   // делает запись в протокол

class Customer
{
public:
   Customer(const Customer& rhs);
   Customer& operator=(const Customer& rhs);
private:
   std::string name;
};

Customer::Customer(const Customer& rhs)
   : name(rhs.name)
{
   logCall("gfgfgfgfgfgfgdgf");
}

Customer& Customer::operator=(const Customer& rhs)
{
   logCall("gfgfgfgfgfgfgdgf");
   name = rhs.name;

   return *this;
}

class PriorityCustomer : public Customer  // производный класс
{
public:
   PriorityCustomer(const PriorityCustomer& rhs);
   PriorityCustomer& operator=(const PriorityCustomer& rhs);
private:
   int priority;
};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
   : Customer(rhs)   // вызвать копирующий конструктор базового класса
   , priority(rhs.priority)
{
   logCall("gfgfgfgfgfgfgdgf");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
   logCall("gfgfgfgfgfgfgdgf");

   Customer::operator=(rhs);  // присвоить значения данным-членам базового класса
   priority = rhs.priority;

   return *this;
}

// если констуктор копирования и оператор присваивания содержат похожий код, вынесете дубл. код в в функцию init()

/**********************************************************************************************/

class Investment {
public:
   bool isTaxFree() const;
};

Investment *createStatement();

int daysHeld(const Investment *pi); // возвращает кол. дней хранения инвестиций

void foo()
{
   std::shared_ptr<Investment> pInv(createStatement()); // использовать фабричную функцию

   int days = daysHeld(pInv.get());
   bool taxeblel = !(pInv->isTaxFree());
}
/*********************************************************************************************/
class FontHandle {};

FontHandle getFont();

void releaseFont(FontHandle fh);

class Font {   // класс RAII
public:
   explicit Font(FontHandle fh)  // захватить ресурс
      : f(fh)
   {}

   FontHandle get() const        // функция явного преобразования
   {
      return f;
   }
   operator FontHandle() const   // функция неявного преобразования
   {
      return f;
   }
   ~Font() { releaseFont(f); } // освободить ресурс

private:
   FontHandle f;  // управляющий ресурс - шрифт
};

void changeFontSize(FontHandle f, int newSize) 
{
} // из API

Font f(getFont());
int newFontSize;
{
   changeFontSize(f, newFontSize); // неявное преобразование
   changeFontSize(f.get(), newFontSize); // явное преобразование
}
/**********************************************************************************************/
int priority();
void processWidgets(std::shared_ptr<Widget> pw, int priority);

{
   processWidgets(std::shared_ptr<Widget>(new Widget), priority()); // error

   std::shared_ptr<Widget> pw(new Widget);
   processWidgets(pw, priority());
}

/*********************************************************************************************/
class DateOld {
public:
   DateOld(int month, int day, int year); // ошибка параметры могут переданы в неверном порядке
   /*...*/
};

struct Day
{
   explicit Day(int d)
      : val(d) {}
   
   int val;
};

class Mounth
{
public:
   static Mounth January()    { return Mounth(1); }
   static Mounth February()   { return Mounth(2); }
   static Mounth March()      { return Mounth(3); }
   static Mounth April()      { return Mounth(4); }
   static Mounth May()        { return Mounth(5); }
   static Mounth June()       { return Mounth(6); }
   static Mounth July()       { return Mounth(7); }
   static Mounth August()     { return Mounth(8); }
   static Mounth September()  { return Mounth(9); }
   static Mounth October()    { return Mounth(10); }
   static Mounth November()   { return Mounth(11); }
   static Mounth December()   { return Mounth(12); }

private:
   explicit Mounth(int m)
      : val(m) {}

   int val;
};

struct Year
{
   explicit Year(int y)
      : val(y) {}

   int val;
};

class Date {
public:
   Date(const Mounth& m, const Day& d, const Year& y);
   /*...*/
};


DateOld d1(3, 4, 1990); // error
Date d2(Mounth::April, Day(3), Year(1990));
Date d3(Mounth(3), Day(4), Year(1990)); // error

/**********************************************************************************************/
// встроенные типы данных, итераторы и обьекты STL - передавать по ссылке

class Rational {
public:
   Rational(int numerator = 0, int denominator = 1);

private:
   int n, d;

   /*
   friend const Rational& operator*(const Rational& lhs, const Rational& rhs) // error: не пытайтесь вернуть ссылку когда должны вернуть объект
   {
      Rational result(lhs.n*rhs.n, lhs.d*rhs.d);
      return result;
   }
   */

   inline const Rational operator*(const Rational& lhs, const Rational& rhs)
   {
      return Rational(lhs.n*rhs.n, lhs.d*rhs.d);
   }
};

/*********************************************************************************************/
// если преобразование типов должно быть применимо ко все параметрам функции(включая и скрытый параметр this), то функция не должна быть членом класса
class Rational {
public:
   Rational(int numerator = 0, int denominator = 1);
                                                         // не содержит operator*
   int numerator() const;     // функция доступа к числителю
   int denominator() const;   // к знаменателю

private:
   int n, d;   
};

const Rational operator*(const Rational& lhs, const Rational& rhs)
{
   return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

Rational oneFourth(1, 4);
Rational result;

result = oneFourth * 2;
result = 2 * oneFourth;

/***********************************************************************************************/
// альтернатива dynamic_cast

class Window
{
public:
   virtual void blink() {}
};


class SpecialWindow : public Window {
public:
   virtual void blink() {}
};

std::vector<std::shared_ptr<Window>> winPtrs;
for (std::vector<std::shared_ptr<Window>>::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
{
   (*iter)->blink();
}
/**********************************************************************************************/
// дескрипторы(handles) - ссылки, указатели, итераторы внутренних данных объекта
class Point {
public:
   Point(int x, int y) {}

   void setX(int newVal);
   void setY(int newVal);
};

class Point;

struct RectData {
   Point ulhc; // верхний левый угол
   Point lrhc; // нижний правый угол
};

class Rectangle {
public:
   const Point& upperLeft() const { return pData->ulhc; }
   const Point& lowerRight() const { return pData->lrhc; }

private:
   std::shared_ptr<RectData> pData;
};
/**********************************************************************************************/
// мьютекс для синхронизации доступа

class Mutex;

class Lock // класс для управления ресурсами с подсчет ссылок на ресурс
{
public:
   explicit Lock(Mutex *pm)
      : mutexPrt(pm, unlock)
   { lock(mutexPrt.get()); }

private:
   std::shared_ptr<Mutex> mutexPrt;
};

class Image;

class PrettyMenu {
public:
   void changeBackground(std::istream& imgSrc) // сменить фоновую картинку
   {
      Lock m1(&mutex1);                 // захват мьютекса

      bgImage.reset(new Image(imgSrc)); /* заменить внутренний указатель bgImage результатом
                                        выражения new Image */
      //delete bgImage;               // избавиться от старой картинки
      ++imageChanges;
      //bgImage = new Image(imgSrc);  // установить новый фон
   }

private:
   Mutex mutex1;      // мьютекс объекта


   // Image *bgImage;   // текущая фоновая картинка
   std::shared_ptr<Image> bgImage;  // текущая фоновая картинка
   int imageChanges;                // сколько раз она менялась
};
/**********************************************************************************************/
// Уменьшение зависимости, отделение интерфейса от реализации

// 1.Идиома Pimpl ( pointer to implementation - указатель на реализацию )

class PersonImpl; // реализация

class Date;
class Address;

class Person { // представление интерфейса. Класс-дискриптор(handle class) - переадресация всех
public:
   Person(const std::string& name, const Date& birthday, const Address& addr) 
      : pImpl(new Person(name, birthday, addr))
   {
   }

   std::string name() const
   {
      return pImpl->name();
   }

   std::string birthday() const;
   std::string address() const;

private:
   std::shared_ptr<PersonImpl> pImpl; // указатель на реализацию
};

// 2.Interface class

class Person { // представление интерфейса
public:
   virtual ~Person();

   virtual std::string name() const = 0;
   virtual std::string birthday() const = 0;
   virtual std::string address() const = 0;

   static std::shared_ptr<Person> create(const std::string& name,   // возвращает shared_ptr на новый экземпляр Person,инициализированный заданными параметрами 
      const Date& birthday,
      const Address& addr)
   {
      return std::shared_ptr<Person>(new RealPerson(name, birthday, addr));
   }
};

class RealPerson : public Person
{
public:
   RealPerson(const std::string& name, const Date& birthday, const Address& addr)
      : theName(name)
      , theBirthDate(birthday)
      , theAddress(addr)
   {
   }

   virtual ~RealPerson() {}

   std::string name() const;
   std::string birthday() const;
   std::string address() const;  

private:
   std::string theName;
   Date theBirthDate;
   Address theAddress;
};

{
   std::string name;
   Date datefBirth;
   Address address;

   // создаем объект поддерживающий интерфейс Person
   std::shared_ptr<Person> pp(Person::create(name, datefBirth, address));

   std::cout << pp->name()       // использовать объект через интерфейс Person
      << pp->birthday()
      << pp->address();
}

/**********************************************************************************************/
class Base
{
public:
   virtual void mf1() = 0;
   virtual void mf1(int);

   virtual void mf2();

   void mf3();
   void mf3(double);
private:
   int x;
};

class Derived : public Base
{
public:
   using Base::mf1;  // обеспечить видимость всех имем
   using Base::mf3;

   virtual void mf1();
   void mf3();
   void mf4();
};

// закрытое наследование

class Base
{
public:
   virtual void mf1() = 0;
   virtual void mf1(int);

   virtual void mf2();
};

class Derived : private Base
{
public:
   virtual void mf1()
   {
      Base::mf1();   // перенаправляющая ф-ция, неявно встроена
   }
};

/**********************************************************************************************/
// Шаблонный метод(англ.Template method)

class GameCharacter
{
public:
   int healthValue() const
   {
      int retVal = doHealthValue();
      return retVal;
   }

private:
   virtual int doHealthValue() const; // производные классы могут переопределить эту функцию

};

GameCharacter::GameCharacter()
{
}

GameCharacter::~GameCharacter()
{
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/


/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/

int main() {
    char a = 'a';
    char z = 'z';
    std::cout << (a < z);
    return 0;
}
