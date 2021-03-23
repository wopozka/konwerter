Konwerter-0.2.0 

WST�P

  Niejednokrotnie pisz�c d�u�sze teksty przy wykorzystaniu doskona�ego
systemu sk�adu tekstu, kt�rym jest LaTeX, pojawia�a si� potrzeba dodania
do tekstu rysunk�w, zawieraj�cych obiekty, kt�re wymaga�y odwo�ywania si� 
do nich w tek�cie dokumentu poprzez numerek. Wi�za�o si� to z konieczno�ci� 
r�cznego ich numerowania, gdy� LaTeX, nie posiada mechanizmu 
umo�liwiaj�cego zautomatyzowanie tej czynno�ci. Taka metoda pracy
powodowa�a, �e ka�de dodanie nowego obrazka poci�ga�o za sob� konieczno��
przenumerowywania wszystkich pozosta�ych. Przysparza�o to autorowi
du�o pracy, oraz by�o bardzo czasoch�onnym zaj�ciem. 

  Program konwerter rozwi�zuje ten problem. U�ywaj�c go, nie numerujesz
obiekt�w na obrazkach, tylko je nazywasz. R�wnie� w tek�cie odnosisz si�
do nich poprzez nazw�. Gdy tekst jest gotowy, uruchomienie programu
konwerter spowoduje zamian� nazw (zwanych dalej etykietkami) na numerki,
zar�wno w plikach eps, jak i w tek�cie. Numery s� nadawane w zale�no�ci 
od kolejno�ci pojawiania si� w plikach eps, a do dyspozycji u�ytkownik
ma 5 typ�w numeracji: 
- cyfry arabskie
- cyfry rzymskie ma�e
- cyfry rzymskie wielkie
- literki ma�e
- literki wielkie

  Wszystkie te typy numeracji, mo�na jednocze�nie u�ywa� w jednym dokumencie.
Dodatkowo mog� si� pojawi� indeksy literowe na przyk�ad: 1a, 2b, Ia itd, 
lecz nie s� one ustawiane automatycznie. O tym co b�dzie indeksem, decyduje
autor tekstu.

  Program pracuje tylko i wy��cznie na plikach eps. Jednak nie wszystkie
programy produkuj� odpowiedni plik graficzny. Zobacz list� wspieranych
program�w, aby sprawdzi� kt�re dzia�aj�.

WYMAGANIA DO KOMPILACJI

GNU make
g++ w wersji 3.0 i wy�szej

KOMPILACJA

  Kompilacja wygl�da identycznie jak dla wszystkich system�w uniksowych. 
Pierwszym etapem b�dzie edycja pliku Makefile, w kt�rym nale�y ustawi�
zmienn� DESTDIR na katalog, do kt�rego chcemy zainstalowa� program.
Domy�lnie jest to /usr/local/bin i je�li nic nie zmienimy, to tam 
w�a�nie program zostanie zainstalowany. Po edycji nale�y skompilowa�
zainstalowa� program przy pomocy poni�szych komend  (druga komenda, 
w zale�no�ci od DESTDIR, mo�e wymaga� uprawnie� superu�ytkownika):

1. make
2. make install

DZIA�ANIE

  Program czyta plik tex, w poszukiwaniu grafik eps. W razie znalezienia 
takowej, jest ona przeszukiwana w celu znalezienia etykiet. Etykiety te 
s� kolejkowane, a nast�pnie zamieniane na numerki. Drugim etapem jest zamiana 
etykiet w pliku texowym. U�ytkownik jako wynik dostaje plik nazwa.tex.auto, 
kt�ry trzeba ponownie skompilowa� latexem. Po tej operacji dostajemy plik 
wynikowy dvi, w kt�rym etykiety powinny by� ju� pozamieniane na numerki, 
zar�wno w plikach eps, jak i w pliku tex. Nale�y zauwa�y�, �e o ile oryginalny
plik tex, nie jest zmieniany, o tyle pliki eps tak. Mo�na bez problemu 
przywr�ci� oryginaln� form� plikom eps, uruchamiaj�c konwerter z odpowiedni� 
opcj� na oryginalnym pliku tex.

U�YCIE PROGRAMU

  Prawid�owe dzia�anie programu wymaga pojawienia si� w plikach eps odpowiednio
zbudowanych etykiet. Mog� one zawiera� dowolne litery j�zyka angielskiego oraz 
cyfry. Niedozwolone jest u�ycie kropki, �rednika i dwukropka gdy� s� one 
wykorzystywane w innym celu. U�ycie podkre�lenia "_" r�wnie� nie jest wskazane
gdy� ma on specjalne znaczenie dla LaTeXa. Nie powinno r�wnie�
powodowa� b��d�w u�ycie polskich liter lecz nie jest to zalecane. 
Etykieta mo�e mie� do 200 znak�w.

  Ka�da etykieta powinna si� zaczyna� konstrukcj� steruj�c�, informuj�c� 
o sposobie jej numerowania. Brak takiej konstrukcji, powoduje �e etykieta 
zostaje automatycznie ponumerowana w spos�b domy�lny. Istnieje pi�� 
konstrukcji steruj�cych: 
:r - ma�e liczby rzymskie 
:R - wielkie liczby rzymskie 
:a - liczby arabskie
:l - ma�e literki
:L - du�e literki
  Cz�sto stosowan� metod� numerowania jest dodawanie indeks�w literowych do 
liczb np. 1a, 1b, 1c itd. Konwerter r�wnie� w znacznym stopniu pomaga tworzy�
takie numerki. Aby to uzyska�, wystarczy �e do etykietki dodasz na ko�cu kropk�,
a po kropce liter�, kt�ra tam powinna si� znale��. Niedozwolone jest
wyst�powanie po kropce dw�ch znak�w, gdy� wtedy program nie potraktuje
tego jako indeksu literowego.

PRZYGOTOWANIE PLIK�W EPS:

  W schemacie ka�dy obiekt podpisujemy etykiet� w nast�puj�cy spos�b:

?et{etykieta;numer}

- etykieta - dowolna etykieta stworzona wed�ug opisu powy�ej;
- numer-(dowolna liczba wi�ksza od zera).
  Poniewa� plik eps jest czytany sekwencyjnie i etykiety niekoniecznie 
b�d� si� pojawia� w odpowiedniej kolejno�ci, konieczne jest ich ponumerowanie
w pliku eps. Dzi�ki temu zostanie zachowana odpowiednia kolejno��.
Numery nie musz� by� kolejnymi liczbami. Brak numeru spowoduje b��dne 
numerowanie etykiet. Numery mog� si� powtarza� ale r�wnie� mo�e to spowodowa�
b��dy.
Przyk�ad u�ycia
?et{benzen;1} - u�yty zostanie domy�lny styl numerowania
?et{:Rbenzen;2} - u�yty zostanie styl numerowania wielkimi liczbami rzymskimi
?et{:rbenzen;3} - u�yty zostanie styl numerowania ma�ymi liczbami rzymskimi
?et{:rbenzen.a;4} - u�yty zostanie ten sam numer co dla etykiety powy�szej
 		    lecz, dodatkowo zostanie dodana literka a np. ia, iia itd.
?et{heksan.a;5} - u�yty zostanie domy�lny styl numerowania i dodatkowo przy 
		  numerku pojawi si� literka a np. 2a, 2b

  Wa�ne jest aby pami�ta�, �e dla programu etykiety :Rbenzen oraz :rbenzen to 
dwie r�ne etykiety i b�d� im przydzielone r�ne numerki, oraz �e w przypadku
pojawienia si� etykiet ?et{heksan.a;1} i ?et{heksan;2} w jednym b�d� wielu 
pliku eps,  obie dostan� ten sam numerek, tyle �e pierwsza dodatkowo indeks 
a - czyli w tym przypadku b�dzie to: 2a i 2.

PLIKI LaTeX
  
  Pliki tex te� wymagaj� dopowiedniego przygotowania. Poniewa� nie wszystkie
pliki eps zawieraj� etykietki oraz z powodu tego, �e w LaTeX nie ma jednej
metody za��czania rysunk�w do tekstu, konwerter wyszukuje w kodzie tex, 
instrukcji nakazuj�cej mu przeszukanie pliku. Aby wskaza� mu plik eps
zawieraj�cy etykietki nale�y u�y� konstrukcji:
%?plik{nazwa_pliku}

  Jest to komentarz dla LaTeXa i nie zostanie on wy�wietlony nigdzie w tek�cie.
Instrukcji tej nie mog� poprzedza� �adne inne znaki, musi to by� pierwszy tekst 
w nowej linijce. Po znalezieniu tego, program konwerter b�dzie przeszukiwa� plik
nazwa_pliku w poszukiwaniu etykiet.

  Warto zaznaczy�, �e polecenie %?plik{nazwa_pliku} nie musi si� odnosi�
koniecznie do pliku eps. Mo�e to by� dowolny plik tekstowy, zawieraj�cy
odpowiednio zbudowane etykietki (patrz przygotowanie etykiet). Umo�liwia nam
to po�rednie sterowanie numeracj�.

  Aby odwo�ywa� si� w tek�cie do etykiet nale�y stworzy� odpowiednie polecenie.
(\newcommand). Domy�lnie jest to \nrzw{etykietka},  lecz mo�e by� to zmienione, 
poprzez u�ycie odpowiedniej opcji wywo�ania programu (patrz OPCJE WYWO�ANIA  
PROGRAMU). Konstrukcja \nrzw{etykietka} mo�e pojawi� si� w dowolnym miejscu 
w linijce tekstu i nie musi by� pierwsz� w danym wierszu. Pozwala to na
swobodne pisanie, bez zwracania uwagi na formatowanie (w ko�cu to TeX powinien
za nas to zrobi�). Etykieta ma posta� dok�adnie tak� sam� jak w pliku eps, po
odrzuceniu numerka po �redniku i samego �rednika. Za��my na przyk�ad �e w plik 
eps wygl�da nast�puj�co:
?et{benzen.a;1}
?et{:Rtoluen;2}
?et{:rksylen;3}
?et{benzen.b},
to w tek�cie dokumentu nale�y umie�ci�: \nrzw{benzen.a}, \nrzw{:Rtoluen}, 
\nrzw{:rksylen}, \nrzw{benzen.b}. Je�li umie�cimi dodatkowo w tek�cie
\nrzw{benzen}, to r�wnie� zostanie to ponumerowane, pomimo �e w plikach eps
jak do tej pory si� to nie pojawi�o(b�dzie mia�o ten sam numerek co etykietki
benzen.a i benzen.b, tylko bez indeksu literowego). Wynika to ze sposobu 
dzia�ania programu i wed�ug autora jest to poprawne.

  Po przetworzeniu pliku o nazwie plik.tex programem konwerter otrzymamy
nowy plik o nazwie plik.tex.auto w kt�rym powy�sze etykiety zostan� zamienione 
na np: zwi�zek \nrzw{3} reaguje z \nrzw{4} daj�c... Plik plik.tex.auto nale�y 
przetworzy� ponownie programem latex.

  Program konwerter rozpoznaje polecenie LaTeXowe \input{}, dzi�ki czemu mo�liwe
jest przetwarzanie dokument�w sk�adaj�cych si� z wielu plik�w.

  Czasami mo�e by� niezb�dne aby, od jakiego� miejsca w tek�cie (na przyk�ad
nowy rozdzia�) rozpocz�� numeracj� od nowa. Program konwerter umo�liwia i to.
W tym celu wystarczy w pliku tex umie�ci� jedn� z poni�szych instrukcji:
%--set-r-to a
%--set-R-to a
%--set-a-to a
%--set-l-to a
%--set-L-to a
Spowoduj� one ustawienie licznika dla odpowiednio liczba rzymskich ma�ych
i wielkich, liczb arabskich oraz liter ma�ych i wielkich na liczb� a. "a" 
musi by� liczb�, czyli dla %--set-l-to i %--set-L-to r�wnie� musi si� pojawi�
liczba. O ile b�dzie to potrzebne, zostanie dodana mo�liwo�� ustwiania licznik�w
dla liter w postaci liter. Przyk�ady u�ycia
%--set-R-to 12 - ustawienie licznika wielkich cyfr rzymskich na 12
%--set-a-to 21 - ustawienie licznika liczb arabskich na 21
Powy�sze instrukcje musz� zaczyna� si� od nowej linijki.
  Czasami podczas pisania, mo�e pojawi� si� konieczno�� zmiany
domy�lnego stylu numeracji, dla danego rozdzia�u. Konwerter wspiera
r�wnie� t� opcj�. W tym celu wystarczy w pliku �r�d�owym tex umie�ci�
polecenie:
%--set-d-to K, 
gdzie K mo�e by�: r, R, a, l, L. Warto r�wnie� zaznaczy�, �e opcje te
dzia�aj� tylko na nowe etykiety. Etykiety, kt�re pojawi�y si� ju�
wcze�niej, b�d� mia�y poprzedni numer.

J�ZYK I OPCJE WYWO�ANIA PROGRAMU 
  Program konwerter obs�uguje obecnie dwa j�zyki: angielski
(domy�lnie) i polski. J�zyk ustawiany na podstawie zmiennej
�rodowiskowej LANG. Je�li jest ona ustawiona na pl_PL, program b�dzie
m�wi� po polsku, w przeciwnym wypadku j�zykiem komunikat�w b�dzie
angielski.
  Wpisz konwerter --help, aby zobaczy� opcje wraz z kr�tk� charakterystyk�.

WSPIERANE PROGRAMY
1) ChemDraw z pakietu ChemOffice.
2) Xfig - program do grafiki wektorowej dla linuksa.
3) Chemtool - program do rysowania wzor�w chemicznych dla linuksa.
  
PRZYK�ADOWE U�YCIE

  Program rozpoznaje z jak� nazw� zosta� wywo�any. Wywo�anie nazw� konwerter
jest r�wnoznaczne z wywo�aniem: konwerter -ltn, natomiast wywo�anie etykietuj
jest r�wnoznaczne z: konwerter -ntl. Oto kilka przyk�ad�w u�ycia:

konwerter -dns R  plik.tex - zamie� etykiety na numery w pliku plik.tex 
			     i wymienionych  w nim plikach eps, stosuj�c 
			     jako domy�lny styl numeracji cyfry rzymskie 
			     wielkie.

etykietuj -ltn -dns R plik.tex    - j.w.

konwerter -ntl plik.tex    - zamie� numery na etykiety w plikach eps 
			     wymienionych w pliku plik.tex

etykietuj plik.tex -         j.w.

konwerter -iss plik.tex    - zamie� etykiety na numerki ignoruj�c wyst�pienia 
			     $--set-counter-to

konwerter -if plik.tex	   - zamie� etykietki na numerki stosuj�c domy�lny 
			     styl numeracji dla wszystkich etykiet.


AUTOR
Piotr Wawrzyniak piti@eliksir.ch.pw.edu.pl
W razie pyta� prosz� kontaktowa� si� na powy�szy adres.
Mi�ego u�ytkowania.
