Konwerter-0.2.0 

WSTÊP

  Niejednokrotnie pisz±c d³u¿sze teksty przy wykorzystaniu doskona³ego
systemu sk³adu tekstu, którym jest LaTeX, pojawia³a siê potrzeba dodania
do tekstu rysunków, zawieraj±cych obiekty, które wymaga³y odwo³ywania siê 
do nich w tek¶cie dokumentu poprzez numerek. Wi±za³o siê to z konieczno¶ci± 
rêcznego ich numerowania, gdy¿ LaTeX, nie posiada mechanizmu 
umo¿liwiaj±cego zautomatyzowanie tej czynno¶ci. Taka metoda pracy
powodowa³a, ¿e ka¿de dodanie nowego obrazka poci±ga³o za sob± konieczno¶æ
przenumerowywania wszystkich pozosta³ych. Przysparza³o to autorowi
du¿o pracy, oraz by³o bardzo czasoch³onnym zajêciem. 

  Program konwerter rozwi±zuje ten problem. U¿ywaj±c go, nie numerujesz
obiektów na obrazkach, tylko je nazywasz. Równie¿ w tek¶cie odnosisz siê
do nich poprzez nazwê. Gdy tekst jest gotowy, uruchomienie programu
konwerter spowoduje zamianê nazw (zwanych dalej etykietkami) na numerki,
zarówno w plikach eps, jak i w tek¶cie. Numery s± nadawane w zale¿no¶ci 
od kolejno¶ci pojawiania siê w plikach eps, a do dyspozycji u¿ytkownik
ma 5 typów numeracji: 
- cyfry arabskie
- cyfry rzymskie ma³e
- cyfry rzymskie wielkie
- literki ma³e
- literki wielkie

  Wszystkie te typy numeracji, mo¿na jednocze¶nie u¿ywaæ w jednym dokumencie.
Dodatkowo mog± siê pojawiæ indeksy literowe na przyk³ad: 1a, 2b, Ia itd, 
lecz nie s± one ustawiane automatycznie. O tym co bêdzie indeksem, decyduje
autor tekstu.

  Program pracuje tylko i wy³±cznie na plikach eps. Jednak nie wszystkie
programy produkuj± odpowiedni plik graficzny. Zobacz listê wspieranych
programów, aby sprawdziæ które dzia³aj±.

WYMAGANIA DO KOMPILACJI

GNU make
g++ w wersji 3.0 i wy¿szej

KOMPILACJA

  Kompilacja wygl±da identycznie jak dla wszystkich systemów uniksowych. 
Pierwszym etapem bêdzie edycja pliku Makefile, w którym nale¿y ustawiæ
zmienn± DESTDIR na katalog, do którego chcemy zainstalowaæ program.
Domy¶lnie jest to /usr/local/bin i je¶li nic nie zmienimy, to tam 
w³a¶nie program zostanie zainstalowany. Po edycji nale¿y skompilowaæ
zainstalowaæ program przy pomocy poni¿szych komend  (druga komenda, 
w zale¿no¶ci od DESTDIR, mo¿e wymagaæ uprawnieñ superu¿ytkownika):

1. make
2. make install

DZIA£ANIE

  Program czyta plik tex, w poszukiwaniu grafik eps. W razie znalezienia 
takowej, jest ona przeszukiwana w celu znalezienia etykiet. Etykiety te 
s± kolejkowane, a nastêpnie zamieniane na numerki. Drugim etapem jest zamiana 
etykiet w pliku texowym. U¿ytkownik jako wynik dostaje plik nazwa.tex.auto, 
który trzeba ponownie skompilowaæ latexem. Po tej operacji dostajemy plik 
wynikowy dvi, w którym etykiety powinny byæ ju¿ pozamieniane na numerki, 
zarówno w plikach eps, jak i w pliku tex. Nale¿y zauwa¿yæ, ¿e o ile oryginalny
plik tex, nie jest zmieniany, o tyle pliki eps tak. Mo¿na bez problemu 
przywróciæ oryginaln± formê plikom eps, uruchamiaj±c konwerter z odpowiedni± 
opcj± na oryginalnym pliku tex.

U¯YCIE PROGRAMU

  Prawid³owe dzia³anie programu wymaga pojawienia siê w plikach eps odpowiednio
zbudowanych etykiet. Mog± one zawieraæ dowolne litery jêzyka angielskiego oraz 
cyfry. Niedozwolone jest u¿ycie kropki, ¶rednika i dwukropka gdy¿ s± one 
wykorzystywane w innym celu. U¿ycie podkre¶lenia "_" równie¿ nie jest wskazane
gdy¿ ma on specjalne znaczenie dla LaTeXa. Nie powinno równie¿
powodowaæ b³êdów u¿ycie polskich liter lecz nie jest to zalecane. 
Etykieta mo¿e mieæ do 200 znaków.

  Ka¿da etykieta powinna siê zaczynaæ konstrukcj± steruj±c±, informuj±c± 
o sposobie jej numerowania. Brak takiej konstrukcji, powoduje ¿e etykieta 
zostaje automatycznie ponumerowana w sposób domy¶lny. Istnieje piêæ 
konstrukcji steruj±cych: 
:r - ma³e liczby rzymskie 
:R - wielkie liczby rzymskie 
:a - liczby arabskie
:l - ma³e literki
:L - du¿e literki
  Czêsto stosowan± metod± numerowania jest dodawanie indeksów literowych do 
liczb np. 1a, 1b, 1c itd. Konwerter równie¿ w znacznym stopniu pomaga tworzyæ
takie numerki. Aby to uzyskaæ, wystarczy ¿e do etykietki dodasz na koñcu kropkê,
a po kropce literê, która tam powinna siê znale¼æ. Niedozwolone jest
wystêpowanie po kropce dwóch znaków, gdy¿ wtedy program nie potraktuje
tego jako indeksu literowego.

PRZYGOTOWANIE PLIKÓW EPS:

  W schemacie ka¿dy obiekt podpisujemy etykiet± w nastêpuj±cy sposób:

?et{etykieta;numer}

- etykieta - dowolna etykieta stworzona wed³ug opisu powy¿ej;
- numer-(dowolna liczba wiêksza od zera).
  Poniewa¿ plik eps jest czytany sekwencyjnie i etykiety niekoniecznie 
bêd± siê pojawiaæ w odpowiedniej kolejno¶ci, konieczne jest ich ponumerowanie
w pliku eps. Dziêki temu zostanie zachowana odpowiednia kolejno¶æ.
Numery nie musz± byæ kolejnymi liczbami. Brak numeru spowoduje b³êdne 
numerowanie etykiet. Numery mog± siê powtarzaæ ale równie¿ mo¿e to spowodowaæ
b³êdy.
Przyk³ad u¿ycia
?et{benzen;1} - u¿yty zostanie domy¶lny styl numerowania
?et{:Rbenzen;2} - u¿yty zostanie styl numerowania wielkimi liczbami rzymskimi
?et{:rbenzen;3} - u¿yty zostanie styl numerowania ma³ymi liczbami rzymskimi
?et{:rbenzen.a;4} - u¿yty zostanie ten sam numer co dla etykiety powy¿szej
 		    lecz, dodatkowo zostanie dodana literka a np. ia, iia itd.
?et{heksan.a;5} - u¿yty zostanie domy¶lny styl numerowania i dodatkowo przy 
		  numerku pojawi siê literka a np. 2a, 2b

  Wa¿ne jest aby pamiêtaæ, ¿e dla programu etykiety :Rbenzen oraz :rbenzen to 
dwie ró¿ne etykiety i bêd± im przydzielone ró¿ne numerki, oraz ¿e w przypadku
pojawienia siê etykiet ?et{heksan.a;1} i ?et{heksan;2} w jednym b±d¼ wielu 
pliku eps,  obie dostan± ten sam numerek, tyle ¿e pierwsza dodatkowo indeks 
a - czyli w tym przypadku bêdzie to: 2a i 2.

PLIKI LaTeX
  
  Pliki tex te¿ wymagaj± dopowiedniego przygotowania. Poniewa¿ nie wszystkie
pliki eps zawieraj± etykietki oraz z powodu tego, ¿e w LaTeX nie ma jednej
metody za³±czania rysunków do tekstu, konwerter wyszukuje w kodzie tex, 
instrukcji nakazuj±cej mu przeszukanie pliku. Aby wskazaæ mu plik eps
zawieraj±cy etykietki nale¿y u¿yæ konstrukcji:
%?plik{nazwa_pliku}

  Jest to komentarz dla LaTeXa i nie zostanie on wy¶wietlony nigdzie w tek¶cie.
Instrukcji tej nie mog± poprzedzaæ ¿adne inne znaki, musi to byæ pierwszy tekst 
w nowej linijce. Po znalezieniu tego, program konwerter bêdzie przeszukiwa³ plik
nazwa_pliku w poszukiwaniu etykiet.

  Warto zaznaczyæ, ¿e polecenie %?plik{nazwa_pliku} nie musi siê odnosiæ
koniecznie do pliku eps. Mo¿e to byæ dowolny plik tekstowy, zawieraj±cy
odpowiednio zbudowane etykietki (patrz przygotowanie etykiet). Umo¿liwia nam
to po¶rednie sterowanie numeracj±.

  Aby odwo³ywaæ siê w tek¶cie do etykiet nale¿y stworzyæ odpowiednie polecenie.
(\newcommand). Domy¶lnie jest to \nrzw{etykietka},  lecz mo¿e byæ to zmienione, 
poprzez u¿ycie odpowiedniej opcji wywo³ania programu (patrz OPCJE WYWO£ANIA  
PROGRAMU). Konstrukcja \nrzw{etykietka} mo¿e pojawiæ siê w dowolnym miejscu 
w linijce tekstu i nie musi byæ pierwsz± w danym wierszu. Pozwala to na
swobodne pisanie, bez zwracania uwagi na formatowanie (w koñcu to TeX powinien
za nas to zrobiæ). Etykieta ma postaæ dok³adnie tak± sam± jak w pliku eps, po
odrzuceniu numerka po ¶redniku i samego ¶rednika. Za³ó¿my na przyk³ad ¿e w plik 
eps wygl±da nastêpuj±co:
?et{benzen.a;1}
?et{:Rtoluen;2}
?et{:rksylen;3}
?et{benzen.b},
to w tek¶cie dokumentu nale¿y umie¶ciæ: \nrzw{benzen.a}, \nrzw{:Rtoluen}, 
\nrzw{:rksylen}, \nrzw{benzen.b}. Je¶li umie¶cimi dodatkowo w tek¶cie
\nrzw{benzen}, to równie¿ zostanie to ponumerowane, pomimo ¿e w plikach eps
jak do tej pory siê to nie pojawi³o(bêdzie mia³o ten sam numerek co etykietki
benzen.a i benzen.b, tylko bez indeksu literowego). Wynika to ze sposobu 
dzia³ania programu i wed³ug autora jest to poprawne.

  Po przetworzeniu pliku o nazwie plik.tex programem konwerter otrzymamy
nowy plik o nazwie plik.tex.auto w którym powy¿sze etykiety zostan± zamienione 
na np: zwi±zek \nrzw{3} reaguje z \nrzw{4} daj±c... Plik plik.tex.auto nale¿y 
przetworzyæ ponownie programem latex.

  Program konwerter rozpoznaje polecenie LaTeXowe \input{}, dziêki czemu mo¿liwe
jest przetwarzanie dokumentów sk³adaj±cych siê z wielu plików.

  Czasami mo¿e byæ niezbêdne aby, od jakiego¶ miejsca w tek¶cie (na przyk³ad
nowy rozdzia³) rozpocz±æ numeracjê od nowa. Program konwerter umo¿liwia i to.
W tym celu wystarczy w pliku tex umie¶ciæ jedn± z poni¿szych instrukcji:
%--set-r-to a
%--set-R-to a
%--set-a-to a
%--set-l-to a
%--set-L-to a
Spowoduj± one ustawienie licznika dla odpowiednio liczba rzymskich ma³ych
i wielkich, liczb arabskich oraz liter ma³ych i wielkich na liczb± a. "a" 
musi byæ liczb±, czyli dla %--set-l-to i %--set-L-to równie¿ musi siê pojawiæ
liczba. O ile bêdzie to potrzebne, zostanie dodana mo¿liwo¶æ ustwiania liczników
dla liter w postaci liter. Przyk³ady u¿ycia
%--set-R-to 12 - ustawienie licznika wielkich cyfr rzymskich na 12
%--set-a-to 21 - ustawienie licznika liczb arabskich na 21
Powy¿sze instrukcje musz± zaczynaæ siê od nowej linijki.
  Czasami podczas pisania, mo¿e pojawiæ siê konieczno¶æ zmiany
domy¶lnego stylu numeracji, dla danego rozdzia³u. Konwerter wspiera
równie¿ tê opcjê. W tym celu wystarczy w pliku ¼ród³owym tex umie¶ciæ
polecenie:
%--set-d-to K, 
gdzie K mo¿e byæ: r, R, a, l, L. Warto równie¿ zaznaczyæ, ¿e opcje te
dzia³aj± tylko na nowe etykiety. Etykiety, które pojawi³y siê ju¿
wcze¶niej, bêd± mia³y poprzedni numer.

JÊZYK I OPCJE WYWO£ANIA PROGRAMU 
  Program konwerter obs³uguje obecnie dwa jêzyki: angielski
(domy¶lnie) i polski. Jêzyk ustawiany na podstawie zmiennej
¶rodowiskowej LANG. Je¶li jest ona ustawiona na pl_PL, program bêdzie
mówi³ po polsku, w przeciwnym wypadku jêzykiem komunikatów bêdzie
angielski.
  Wpisz konwerter --help, aby zobaczyæ opcje wraz z krótk± charakterystyk±.

WSPIERANE PROGRAMY
1) ChemDraw z pakietu ChemOffice.
2) Xfig - program do grafiki wektorowej dla linuksa.
3) Chemtool - program do rysowania wzorów chemicznych dla linuksa.
  
PRZYK£ADOWE U¯YCIE

  Program rozpoznaje z jak± nazw± zosta³ wywo³any. Wywo³anie nazw± konwerter
jest równoznaczne z wywo³aniem: konwerter -ltn, natomiast wywo³anie etykietuj
jest równoznaczne z: konwerter -ntl. Oto kilka przyk³adów u¿ycia:

konwerter -dns R  plik.tex - zamieñ etykiety na numery w pliku plik.tex 
			     i wymienionych  w nim plikach eps, stosuj±c 
			     jako domy¶lny styl numeracji cyfry rzymskie 
			     wielkie.

etykietuj -ltn -dns R plik.tex    - j.w.

konwerter -ntl plik.tex    - zamieñ numery na etykiety w plikach eps 
			     wymienionych w pliku plik.tex

etykietuj plik.tex -         j.w.

konwerter -iss plik.tex    - zamieñ etykiety na numerki ignoruj±c wyst±pienia 
			     $--set-counter-to

konwerter -if plik.tex	   - zamieñ etykietki na numerki stosuj±c domy¶lny 
			     styl numeracji dla wszystkich etykiet.


AUTOR
Piotr Wawrzyniak piti@eliksir.ch.pw.edu.pl
W razie pytañ proszê kontaktowaæ siê na powy¿szy adres.
Mi³ego u¿ytkowania.
