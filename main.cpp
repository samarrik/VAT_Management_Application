#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <iterator>
#include <functional>
using namespace std;

/** Class represents datatype "date". */
class CDate
{
public:
  /** Constructor */
  CDate(int y,
        int m,
        int d)
      : m_Year(y),
        m_Month(m),
        m_Day(d)
  {
  }

  /**
   * Method compares two objects of the class CDate
   * @param[in] x The object to compare with
   * @returns 0 if dates are the same, +1 if fisrt is bigger, -1 if the second is smaller
   */
  int compare(const CDate &x) const
  {
    if (m_Year != x.m_Year)
      return m_Year - x.m_Year;
    if (m_Month != x.m_Month)
      return m_Month - x.m_Month;
    return m_Day - x.m_Day;
  }

  int year(void) const
  {
    return m_Year;
  }

  int month(void) const
  {
    return m_Month;
  }

  int day(void) const
  {
    return m_Day;
  }

  /**
   * Operator << for the class CDate
   * @param[in] os The output stream
   * @param[in] x The CDate value to be printed
   * @returns Output stream with the CDate object in it
   */
  friend ostream &operator<<(ostream &os,
                             const CDate &x)
  {
    char oldFill = os.fill();
    return os << setfill('0') << setw(4) << x.m_Year << "-"
              << setw(2) << static_cast<int>(x.m_Month) << "-"
              << setw(2) << static_cast<int>(x.m_Day)
              << setfill(oldFill);
  }

private:
  int16_t m_Year;
  int8_t m_Month;
  int8_t m_Day;
};

/**
 * Function changes the string to *normailized form (details below)
 * @param[in] src A string to be changed (string isn't copied, the original data is being transformed)
 * @return  A reference to the normalized string
 * @details normalized form - All redundant whitespaces are earsed, all letters
 * are converted to the lowercase
 */
string &normalizedName(string &src)
{
  // Transforms all chars to lowercase
  std::transform(src.begin(), src.end(), src.begin(),
                 [](unsigned char c) -> unsigned char
                 { return std::tolower(c); });

  // Deletes all redundant spaces
  size_t i = 0;
  while (i < src.length())
  {
    if (isspace(src[i]))
    {
      if (i == 0 || i == src.length())
      {
        src.erase(src.begin() + i);
        continue;
      }

      while (isspace(src[i + 1]) && i + 1 <= src.length())
        src.erase(src.begin() + i + 1);

      if (i + 1 == src.length() && isspace(src[i]))
      {
        src.erase(src.begin() + i);
        continue;
      }
    }
    i++;
  }
  return src;
}

/**
 * Function changes all chars in the string to lowercase
 * @param[in] src A string to be changed (string is being copied)
 * @return  A string with all chars in lowercase
 */
string tolowerName(string src)
{
  std::transform(src.begin(), src.end(), src.begin(),
                 [](unsigned char c) -> unsigned char
                 { return std::tolower(c); });
  return src;
}

/**
 * Class represents an invoice
 */
class CInvoice
{
public:
  /**
   * Constructor for the CInvoice element
   * @details m_seller and m_buyer are being normalized at the moment of creating a CInvoice
   */
  CInvoice(const CDate &date,
           const string &seller,
           const string &buyer,
           unsigned int amount,
           double vat)
      : m_date(date),
        m_seller(seller),
        m_buyer(buyer),
        m_amount(amount),
        m_vat(vat)
  {
    normalizedName(m_seller);
    normalizedName(m_buyer);
  }

  /** At the moment no copy/move constr, assignment oper. etc. is needed,
   *   but it can added in the furter version if there will be need in it.
   */

  CDate date(void) const
  {
    return m_date;
  }

  string buyer(void) const
  {
    return m_buyer;
  }

  string seller(void) const
  {
    return m_seller;
  }

  unsigned int amount(void) const
  {
    return m_amount;
  }

  double vat(void) const
  {
    return m_vat;
  }

  // Sets the value m_seller
  void setSeller(const string seller)
  {
    m_seller = seller;
  }

  // Sets the value m_buyer
  void setBuyer(const string buyer)
  {
    m_buyer = buyer;
  }

private:
  // All CInvoice items
  CDate m_date;
  string m_seller;
  string m_buyer;
  size_t m_amount;
  size_t m_vat;
};

/**
 *class Represents an extended interface of the CInvoice
 *@details  Class adds a serial_num to CInvocice, which represents order of loading
 *          CInvoice to the container. It is set when the CInvoice is added to
 *          to register
 */
struct CInvoiceExtd
{
  CInvoiceExtd(const CInvoice &src, const size_t serial_num)
      : m_invoice(src), m_serial_num(serial_num)
  {
  }
  CInvoice m_invoice;
  size_t m_serial_num;
};

/**
 *comparator for CInvoiceExtd objects
 */
struct invoicesExtdCmp
{
  bool operator()(const CInvoiceExtd &el1, const CInvoiceExtd &el2) const
  {
    if (el1.m_invoice.date().compare(el2.m_invoice.date()) < 0)
    {
      return true;
    }
    else if (el1.m_invoice.date().compare(el2.m_invoice.date()) > 0)
    {
      return false;
    }
    else
    {
      if (el1.m_invoice.seller() < el2.m_invoice.seller())
      {
        return true;
      }
      else if (el1.m_invoice.seller() > el2.m_invoice.seller())
      {
        return false;
      }
      else
      {
        if (el1.m_invoice.buyer() < el2.m_invoice.buyer())
        {
          return true;
        }
        else if (el1.m_invoice.buyer() > el2.m_invoice.buyer())
        {
          return false;
        }
        else
        {
          if (el1.m_invoice.amount() < el2.m_invoice.amount())
          {
            return true;
          }
          else if (el1.m_invoice.amount() > el2.m_invoice.amount())
          {
            return false;
          }
          else
          {
            if (el1.m_invoice.vat() < el2.m_invoice.vat())
            {
              return true;
            }
            else if (el1.m_invoice.vat() > el2.m_invoice.vat())
            {
              return false;
            }
            else
            {
              return false; // CInvoices are same
            }
          }
        }
      }
    }
  }
};

/**
 *class represents a company in a register
 */
class CCompany
{
public:
  CCompany(const string &name)
      : m_official_name(name)
  {
  }
  friend class CVATRegister;

private:
  string m_official_name;                                   // official name of the company
  set<CInvoiceExtd, invoicesExtdCmp> m_issued;              // Issued invoices of current company
  set<CInvoiceExtd, invoicesExtdCmp> m_mentioned_as_seller; // Accepted invoices of other companies, where current company was mentioned
  set<CInvoiceExtd, invoicesExtdCmp> m_accepted;            // Accepted invoices of current company
  set<CInvoiceExtd, invoicesExtdCmp> m_mentioned_as_buyer;  // Inssued invoics of other companies, where current company was mentioned
};

/**
 *class represents a constructor for making a sequence of comparing rules for CInvoices
 */
class CSortOpt
{
public:
  static const int BY_DATE = 0;
  static const int BY_BUYER = 1;
  static const int BY_SELLER = 2;
  static const int BY_AMOUNT = 3;
  static const int BY_VAT = 4;
  static const int BY_PLACE = 5;

  CSortOpt(void)
  {
  }

  // method adds a sorting rule to the vector of already specified sorting rules
  CSortOpt &addKey(int key,
                   bool ascending = true)
  {
    keys.push_back(make_pair(key, ascending));
    return *this;
  }

  // method returns a vector of specified sorting rules
  vector<pair<int, bool>> getKeys() const
  {
    return keys;
  }

private:
  vector<pair<int, bool>> keys;
};

/**
 *class represents a register of invoices
 *@details Allows managment of invoices
 */
class CVATRegister
{
public:
  CVATRegister(void)
  {
  }

  /**
   * Method registers a company in a register
   * @param[in] name A name of the company to be added
   * @returns true if a new company was added, false if the company with such name already exists
   */
  bool registerCompany(const string &name)
  {
    string cmp_name = name;
    normalizedName(cmp_name);

    auto it = m_companies.find(cmp_name);
    if (it != m_companies.end())
      return false;
    m_companies.insert(make_pair(cmp_name, CCompany(name)));
    return true;
  }
  /**
   * Method adds invoice to the register as issued
   * @param[in] x A CInvoice to be added
   * @returns true if CInvoice was added without problems, false if error happened
   */
  bool addIssued(const CInvoice &x)
  {
    // Logic error buyer and seller can't be the same company
    if (x.buyer() == x.seller())
      return false;

    // Find companies in the map which correspond to m_buyer and m_seller in (CInvoice)x
    auto seller_it = m_companies.find(x.seller());
    auto buyer_it = m_companies.find(x.buyer());

    if (seller_it == m_companies.end() || buyer_it == m_companies.end())
    {
      return false;
    }

    // Set a serial number for the invoice
    CInvoiceExtd el(x, m_serial_num++);

    // Try to add an invoice to the "m_issued" set of the seller, if it works add to set "second.m_mentioned_as_buyer" of the buyer as well
    pair<set<CInvoiceExtd, invoicesExtdCmp>::iterator, bool> res = (seller_it->second.m_issued.insert(el));
    if (res.second)
    { // The CInvoice don't exist
      buyer_it->second.m_mentioned_as_buyer.insert(el);
      return true;
    }
    return false;
  }

  /**
   * Method adds invoice to the register as accepted
   * @param[in] x A CInvoice to be added
   * @returns true if CInvoice was added without problems, false if error happened
   */
  bool addAccepted(const CInvoice &x)
  {
    // Logic error buyer and seller can't be the same company
    if (x.buyer() == x.seller())
      return false;

    // Find companies in the map which correspond to m_buyer and m_seller in (CInvoice)x
    auto seller_it = m_companies.find(x.seller());
    auto buyer_it = m_companies.find(x.buyer());

    if (seller_it == m_companies.end() || buyer_it == m_companies.end())
    {
      return false;
    }

    // Set a serial number for the invoice
    CInvoiceExtd el(x, m_serial_num++);

    // Try to add an invoice to the "m_accepted" set of the buyer, if it works add to set "second.m_mentioned_as_seller" of the seller as well
    pair<set<CInvoiceExtd, invoicesExtdCmp>::iterator, bool> res = (buyer_it->second.m_accepted.insert(el));
    if (res.second)
    { // The CInvoice don't exist
      seller_it->second.m_mentioned_as_seller.insert(el);
      return true;
    }
    return false;
  }

  /**
   * Method deletes issued invoice from the register
   * @param[in] x A CInvoice to be deleted
   * @returns true if CInvoice was deleted without problems, false if error happened
   */
  bool delIssued(const CInvoice &x)
  {
    // Logic error buyer and seller can't be the same company
    if (x.buyer() == x.seller())
      return false;

    // Find companies in the map which correspond to m_buyer and m_seller in (CInvoice)x
    auto seller_it = m_companies.find(x.seller());
    auto buyer_it = m_companies.find(x.buyer());

    if (seller_it == m_companies.end() || buyer_it == m_companies.end())
      return false;

    CInvoiceExtd tmp(x, 0);
    auto it = seller_it->second.m_issued.find(tmp);

    // If there is such invoice, delete it from both sets (issued and mentioned)
    if (it == seller_it->second.m_issued.end())
    {
      return false;
    }
    else
    {
      auto it_mentioned = buyer_it->second.m_mentioned_as_buyer.find(tmp);
      seller_it->second.m_issued.erase(it);
      buyer_it->second.m_mentioned_as_buyer.erase(it_mentioned);
    }
    return true;
  }

  /**
   * Method deletes accepted invoice from the register
   * @param[in] x A CInvoice to be deleted
   * @returns true if CInvoice was deleted without problems, false if error happened
   */
  bool delAccepted(const CInvoice &x)
  {
    // Logic error buyer and seller can't be the same company
    if (x.buyer() == x.seller())
      return false;

    // Find companies in the map which correspond to m_buyer and m_seller in (CInvoice)x
    auto seller_it = m_companies.find(x.seller());
    auto buyer_it = m_companies.find(x.buyer());

    if (seller_it == m_companies.end() || buyer_it == m_companies.end())
      return false;

    CInvoiceExtd tmp(x, 0);
    auto it = buyer_it->second.m_accepted.find(tmp);

    // If there is such invoice, delete it from both sets (accepted and mentioned)
    if (it == buyer_it->second.m_accepted.end())
    {
      return false;
    }
    else
    {
      auto it_mentioned = seller_it->second.m_mentioned_as_seller.find(tmp);
      buyer_it->second.m_accepted.erase(it);
      seller_it->second.m_mentioned_as_seller.erase(it_mentioned);
    }
    return true;
  }

  /**
   * Method returns the list of unmatched Invoices sorted by specified rules
   * @param[in] company A name of the company which unmatched invoces we want to check
   * @param[in] sortBy Rules to sort unmatched invoices
   * @returns a list of unmatched invoices of the following company
   */
  list<CInvoice> unmatched(const string &company, const CSortOpt &sortBy) const
  {
    // A vector, which will be used for manipution with unmatched invoices
    vector<CInvoiceExtd> unmatched;

    // Normalize the name of the company we wnat to check
    string cmp_name = company;
    normalizedName(cmp_name);

    auto it = m_companies.find(cmp_name);
    if (it != m_companies.end())
    {
      // Find symmetric difference
      set_symmetric_difference(it->second.m_issued.begin(), it->second.m_issued.end(), it->second.m_mentioned_as_seller.begin(), it->second.m_mentioned_as_seller.end(), back_inserter(unmatched), invoicesExtdCmp());
      set_symmetric_difference(it->second.m_accepted.begin(), it->second.m_accepted.end(), it->second.m_mentioned_as_buyer.begin(), it->second.m_mentioned_as_buyer.end(), back_inserter(unmatched), invoicesExtdCmp());

      // Add the last key to sort by the serial number of the invoice if all other criteria can't differ two invoices
      CSortOpt sortExtd(sortBy);
      sortExtd.addKey(CSortOpt::BY_PLACE, true);
      vector<pair<int, bool>> keys_vec = sortExtd.getKeys();

      // Bring official names of companies back to the invoice
      for (auto i = unmatched.begin(); i != unmatched.end(); ++i)
      {
        i->m_invoice.setBuyer(m_companies.at(i->m_invoice.buyer()).m_official_name);
        i->m_invoice.setSeller(m_companies.at(i->m_invoice.seller()).m_official_name);
      }

      // Sort the vector according to conditions
      sort(unmatched.begin(), unmatched.end(), [sortExtd, keys_vec](CInvoiceExtd &a, CInvoiceExtd &b)
           {
        for (const auto& condition : keys_vec) {
              if ( condition.first == CSortOpt::BY_DATE ) {
                if ( a.m_invoice.date().compare(b.m_invoice.date()) != 0 ) {
                  if (condition.second) {
                    return a.m_invoice.date().compare(b.m_invoice.date()) < 0 ;
                  }
                  else {
                    return a.m_invoice.date().compare(b.m_invoice.date()) > 0 ;
                  }
                }
              } else if ( condition.first == CSortOpt::BY_BUYER ) {
                if (tolowerName(a.m_invoice.buyer()) != tolowerName(b.m_invoice.buyer())) {
                  if (condition.second) {
                      return tolowerName(a.m_invoice.buyer()) < tolowerName(b.m_invoice.buyer());
                  }
                  else {
                      return tolowerName(a.m_invoice.buyer()) > tolowerName(b.m_invoice.buyer());
                  }
                }
              } else if ( condition.first == CSortOpt::BY_SELLER ) {
                if (a.m_invoice.seller() != b.m_invoice.seller()) {
                  if (condition.second) {
                      return tolowerName(a.m_invoice.seller()) < tolowerName(b.m_invoice.seller());
                  }
                  else {
                      return tolowerName(a.m_invoice.seller()) > tolowerName(b.m_invoice.seller());
                  }
                }
              } else if ( condition.first == CSortOpt::BY_AMOUNT ) {
                if (a.m_invoice.amount() != b.m_invoice.amount()) {
                  if (condition.second) {
                      return a.m_invoice.amount() < b.m_invoice.amount();
                  }
                  else {
                      return a.m_invoice.amount() > b.m_invoice.amount();
                  }
                }
              } else if ( condition.first == CSortOpt::BY_VAT ) {
                if (a.m_invoice.vat() != b.m_invoice.vat()) {
                  if (condition.second) {
                      return a.m_invoice.vat() < b.m_invoice.vat();
                  }
                  else {
                      return a.m_invoice.vat() > b.m_invoice.vat();
                  }
                }
              } else if ( condition.first == CSortOpt::BY_PLACE ) {
                  if (condition.second) {
                      return a.m_serial_num < b.m_serial_num;
                  }
                  else {
                      return a.m_serial_num > b.m_serial_num;
                  }
              }
          }
          return false; });
    }

    // Move contents of the vector to a CInvoice list (extract CInvoice from CInvoiceExtd)
    list<CInvoice> res;
    for (size_t i = 0; i < unmatched.size(); i++)
    {
      res.push_back(move(unmatched[i].m_invoice));
    }
    return res;
  }

private:
  // A map of the companies
  unordered_map<string, CCompany> m_companies;

  // Global serial number value for a one register
  size_t m_serial_num = 0;
};


// Function to compare two lists of CInvoices
bool equalLists(const list<CInvoice> &a, const list<CInvoice> &b)
{
  if (a.size() != b.size())
    return false;

  /*  There is a special situation, CInvoice is already created with normalized name of the
      seller and buyer, so temporary objects which will be used to check the implementation will have a normalized names.
      At the same time as a result of CVATRegister::unmatched we will receive a list of CInvoices where seller/buyer are
      not normalized. So I thought that making a "special" != operator in CInvoice won't be a good idea, so it is stupidly
      implemented here
  */

  auto it_a = a.begin();
  auto it_b = b.begin();

  for (; it_a != a.end(); ++it_a, ++it_b)
  {
    string seller_a = it_a->seller();
    string buyer_a = it_a->buyer();
    string seller_b = it_b->seller();
    string buyer_b = it_b->buyer();
    normalizedName(seller_a);
    normalizedName(seller_b);
    normalizedName(buyer_a);
    normalizedName(buyer_b);

    if (it_a->date().compare(it_b->date()) != 0 ||
        seller_a != seller_b ||
        buyer_a != buyer_b ||
        it_a->amount() != it_b->amount() ||
        it_a->vat() != it_b->vat())
      return false;
  }

  return true;
}

int main(void)
{
  // normalizedName test
  string to_be_normalized = "  Y  oU . thINK yo U c   AN  beat me?  ";
  assert("y ou . think yo u c an beat me?" == normalizedName(to_be_normalized));
  to_be_normalized = "       ";
  assert("" == normalizedName(to_be_normalized));
  to_be_normalized = "";
  assert("" == normalizedName(to_be_normalized));
  cout << "TEST: "
       << "normalizedName()"
       << " PASSED!" << endl;

  // tolowerName test
  assert(" to lower " == tolowerName(" To LoWeR "));
  assert("      k cdsmjio:nld anh j    " == tolowerName("      K cdsMJIO:NLD aNH J    "));
  cout << "TEST: "
       << "tolowerName()"
       << " PASSED!" << endl;

  // Tests for the whole implementation
  CVATRegister r;
  assert(r.registerCompany("first Company"));
  assert(r.registerCompany("Second     Company"));
  assert(r.registerCompany("ThirdCompany, Ltd."));
  assert(r.registerCompany("Third Company, Ltd."));
  assert(!r.registerCompany("Third Company, Ltd."));
  assert(!r.registerCompany(" Third  Company,  Ltd.  "));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 20)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 200, 30)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 30)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "Second Company ", "First Company", 300, 30)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34)));
  assert(!r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
  assert(!r.addIssued(CInvoice(CDate(2000, 1, 4), "First Company", "First   Company", 200, 30)));
  assert(!r.addIssued(CInvoice(CDate(2000, 1, 4), "Another Company", "First   Company", 200, 30)));
  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, false).addKey(CSortOpt::BY_DATE, false)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)}));
  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000)}));
  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_VAT, true).addKey(CSortOpt::BY_AMOUNT, true).addKey(CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)}));
  assert(equalLists(r.unmatched("First Company", CSortOpt()),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)}));
  assert(equalLists(r.unmatched("second company", CSortOpt().addKey(CSortOpt::BY_DATE, false)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Third Company, Ltd.", "Second     Company", 400, 34.000000)}));
  assert(equalLists(r.unmatched("last company", CSortOpt().addKey(CSortOpt::BY_VAT, true)),
                    list<CInvoice>{}));
  assert(r.addAccepted(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company ", 200, 30)));
  assert(r.addAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert(r.addAccepted(CInvoice(CDate(2000, 1, 1), "Second company ", "First Company", 300, 32)));
  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));
  assert(!r.delIssued(CInvoice(CDate(2001, 1, 1), "First Company", "Second Company ", 200, 30)));
  assert(!r.delIssued(CInvoice(CDate(2000, 1, 1), "A First Company", "Second Company ", 200, 30)));
  assert(!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Hand", 200, 30)));
  assert(!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 1200, 30)));
  assert(!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 200, 130)));
  assert(r.delIssued(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company", 200, 30)));
  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));
  assert(r.delAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));
  assert(r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));
  cout << "TEST: "
       << "everything"
       << " PASSED!" << endl;
  return EXIT_SUCCESS;
}