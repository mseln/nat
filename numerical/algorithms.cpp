// Externa funktioner:
// OutIt copy(InIt first, InIt last, OutIt x);
//  Returv�rde: x + N, utiteratorn efter sista elementet.
// void fill(FwdIt first, FwdIt last, const T& x);
// bool next_permutation(BidIt first, BidIt last, Pred pr); // O(n)
//  Funktion: Permuterar m�ngden till n�sta variant enligt lexikal ordning.
//  Kommentar: B�rja med en sorterad m�ngd. Tar ej med dubbletter.
// void nth_element(RanIt fi,RanIt nth, RanIt la [,Pred pr]);
//  Funktion: Delar upp elementen s� att *nth �r st�rre
//  eller lika alla element i [first, nth[
//  och *nth �r mindre eller lika alla element i ]nth, last[.
//  Komplexitet: O(n) i medeltal
// BidIt partition(BidIt first, BidIt last, Pred pr); // O(n)
//  Returv�rde: first + k, iteratorn f�r f�rsta elementet i andra intervallet.
//  Funktion: Delar upp elementen s� att pr() �r sant resp. falskt f�r alla
//  element i intervallen [0, k[ respektive [k, n[.
// FwdIt stable_partition(FwdIt first, FwdIt last, Pred pr);
//  Kommentar: Samma som ovan men bevarar inb�rdes ordning.
// void sort(RanIt first, RanIt last [, Pred pr]); // O(n*log(n))
//  Kommentar: F�r list<> anv�nd den interna funktionen l.sort().
// void stable_sort(RanIt first, RanIt last [, Pred pr]);
//  Kommentar: Samma som ovan men bevarar inb�rdes ordning.
// FwdIt unique(FwdIt first, FwdIt last [, Pred pr]); // O(n)
//  Returv�rde: first + k, iteratorn efter sista elementet i m�ngden.
//  Funktion: Delar upp elementen s� att inga p� varandra f�ljande
//  element i [0, k) �r lika.
//  Elementen i [k, last[ �r odefinierade.
//  Kommentar: F�r list<> anv�nd den interna funktionen l.unique().
//
// S�kning i sorterade m�ngder
// F�ljande funktioner har tidskomplexiteten O(log(n)) med undantaget O(n)
// f�r list. De tre sista samt funktion find() finns internt i map
// och set. Returnerar c.end() om inget passande element hittas.
// bool binary_search(FwdIt first, FwdIt last, T& x [, Pred pr]);
//  Returv�rde: true om x finns, annars false.
// FwdIt lower_bound(FwdIt first, FwdIt last, T& x [, Pred pr]);
//  Returv�rde: first + k, f�rsta positionen som x kan s�ttas
//  in p� s� att sorteringen, dvs. varje element i [0, k[ �r mindre �n x.
// FwdIt upper_bound(FwdIt first, FwdIt last, T& x [, Pred pr]);
//  Returv�rde: first + k, sista positionen som x kan s�ttas
//  in p� s� att sorteringen bibeh�lls, dvs. varje element i
//  ]k, n[ �r st�rre �n x.
// pair<It, It> equal_range(It first, It last, T& x [,Pred pr]);
//  Returv�rde: pair(lower_bound(fi, la, x),upper_bound(fi, la, x))

// Binary search (from Wikipedia)
// The indices are _inclusive_.
int binary_search(T *a, int key, int min, int max) {
  while (min < max) {
    int mid = (min + max) / 2; // midpoint(min, max)

    // assert(mid < max)

    // The condition can be replaced by some other function
    // depending on mid, eg worksFor(mid + 1) to search for
    // the last index "worksFor" returns true for.
    if (a[mid] < key) {
      min = mid + 1;
    } else {
      max = mid;
    }
  }

  // Equality test, can be skipped when looking for a specific value
  if ((max == min) && (a[min] == key))
    return min;
  else
    return NOT_FOUND;
}

// Fenwick tree:
