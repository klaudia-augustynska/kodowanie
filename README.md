# kodowanie
Aplikacja konsolowa w C++, posiadająca 3 funkcje:
- szyfrowanie tekstu (pliku tekstowego)
- deszyfrowanie tekstu (pliku tekstowego)
- opowiadanie o danej metodzie szyfrowania.

Metody te wykorzystują do działania polimorfizm - każdy rodzaj szyfrowania to klasa dziedzicząca po klasie abstrakcyjnej, która posiada metody _encode, decode_ i _rasskazywaj_ o implementacji zależnej od szyfrowania wybranego przez użytkownika.

Program jest przyjazny dla użytkownika, działa w 3 krokach:

1. Wybierz co chcesz zrobić.
2. Wybierz rodzaj kodowania.
3. Podaj tekst lub lokalizację pliku tekstowego.


Rozpoznawane szyfry to:
- szyfr Cezara,
- szyfr ROT13,
- szyfr ROT47,
- kod Morse'a,
- alfabet Braille'a,
- szyfr AtBash,
- szyfr cmentarny,
- szyfr Bacona,
- szyfr Vigenere'a.
