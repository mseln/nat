// Externa funktioner:
// OutIt copy(InIt first, InIt last, OutIt x);
//  Returvärde: x + N, utiteratorn efter sista elementet.
// void fill(FwdIt first, FwdIt last, const T& x);
// bool next_permutation(BidIt first, BidIt last, Pred pr); // O(n)
//  Funktion: Permuterar mängden till nästa variant enligt lexikal ordning.
//  Kommentar: Börja med en sorterad mängd. Tar ej med dubbletter.
// void nth_element(RanIt fi,RanIt nth, RanIt la [,Pred pr]);
//  Funktion: Delar upp elementen så att *nth är större
//  eller lika alla element i [first, nth[
//  och *nth är mindre eller lika alla element i ]nth, last[.
//  Komplexitet: O(n) i medeltal
// BidIt partition(BidIt first, BidIt last, Pred pr); // O(n)
//  Returvärde: first + k, iteratorn för första elementet i andra intervallet.
//  Funktion: Delar upp elementen så att pr() är sant resp. falskt för alla
//  element i intervallen [0, k[ respektive [k, n[.
// FwdIt stable_partition(FwdIt first, FwdIt last, Pred pr);
//  Kommentar: Samma som ovan men bevarar inbördes ordning.
// void sort(RanIt first, RanIt last [, Pred pr]); // O(n*log(n))
//  Kommentar: För list<> använd den interna funktionen l.sort().
// void stable_sort(RanIt first, RanIt last [, Pred pr]);
//  Kommentar: Samma som ovan men bevarar inbördes ordning.
// FwdIt unique(FwdIt first, FwdIt last [, Pred pr]); // O(n)
//  Returvärde: first + k, iteratorn efter sista elementet i mängden.
//  Funktion: Delar upp elementen så att inga på varandra följande
//  element i [0, k) är lika.
//  Elementen i [k, last[ är odefinierade.
//  Kommentar: För list<> använd den interna funktionen l.unique().
//
// Sökning i sorterade mängder
// Följande funktioner har tidskomplexiteten O(log(n)) med undantaget O(n)
// för list. De tre sista samt funktion find() finns internt i map
// och set. Returnerar c.end() om inget passande element hittas.
// bool binary_search(FwdIt first, FwdIt last, T& x [, Pred pr]);
//  Returvärde: true om x finns, annars false.
// FwdIt lower_bound(FwdIt first, FwdIt last, T& x [, Pred pr]);
//  Returvärde: first + k, första positionen som x kan sättas
//  in på så att sorteringen, dvs. varje element i [0, k[ är mindre än x.
// FwdIt upper_bound(FwdIt first, FwdIt last, T& x [, Pred pr]);
//  Returvärde: first + k, sista positionen som x kan sättas
//  in på så att sorteringen bibehålls, dvs. varje element i
//  ]k, n[ är större än x.
// pair<It, It> equal_range(It first, It last, T& x [,Pred pr]);
//  Returvärde: pair(lower_bound(fi, la, x),upper_bound(fi, la, x))

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
