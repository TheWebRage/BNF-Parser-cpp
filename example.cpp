build_first_sets() {

  FirstSets first;

  {
    // The pseudo code in Figure 3.7,
    // says we should do this on the union of the terminals, eof, and E.
    SymbolSet symbols(std::begin(T_Grammar::symbols), std::end(T_Grammar::symbols));
    symbols.emplace(T_Grammar::SYMBOL_EMPTY);
    assert(contains(symbols, T_Grammar::SYMBOL_EOF));

    for (const auto& symbol : symbols) {
      if (symbol.terminal) {
        const SymbolSet temp = {symbol};
        first[symbol] = temp;
        assert(first[symbol] == temp);
        assert(first[symbol].size() == 1);
      } else {
        first[symbol] = {};
      }
    }
  }

  const auto symbols = T_Grammar::symbols;
  const auto& rules = T_Grammar::rules;
  assert(!contains(symbols, T_Grammar::SYMBOL_EMPTY));

  for (const auto& symbol : symbols) {
    if (symbol.terminal) {
      if (first[symbol].size() != 1) {
        std::cerr << "symbol: " << symbol.name << ", first[any terminal] should = the terminal." << std::endl;
      }

      assert(first[symbol].size() == 1);
    }
  }

  bool changing = true;
  while (changing) {
    changing = false;

    for (const auto& rule : rules) {
      const auto& a = rule.first;
      const auto& expansions = rule.second;
      for (const auto& b : expansions) {
        const auto k = b.size();
        if (k == 0) {
          continue;
        }

        const auto& b1 = b[0];
        auto rhs = remove_symbol(first[b1], T_Grammar::SYMBOL_EMPTY);

        // The pseudocode uses 1-indexing, but we use 0-indexing.
        std::size_t i = 0;
        while (contains(first[b[i]], T_Grammar::SYMBOL_EMPTY) && i < (k - 1)) {
          const auto& bip1 = b[i+1];
          const auto more = remove_symbol(first[bip1], T_Grammar::SYMBOL_EMPTY);
          rhs.insert(std::begin(more), std::end(more));
          ++i;
        }

        const auto& bk = b[k-1];
        if (i == (k - 1) && contains(first[bk], T_Grammar::SYMBOL_EMPTY)) {
          rhs.emplace(T_Grammar::SYMBOL_EMPTY);
        }

        auto& firsta = first[a];
        const auto count_before = firsta.size();
        firsta.insert(std::begin(rhs), std::end(rhs));
        changing |= (count_before != firsta.size());
      }
    }
  }

  return first;
}