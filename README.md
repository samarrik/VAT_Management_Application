## Disclamer
This repository contains the code of the task, I've made that small project for the subject [Programming and Algorithms 2](https://courses.fit.cvut.cz/BI-PA2/) studied during the second semester at the Czech Technical University in Prague.

## Description
This application controls companies forwarding invoices to each other. It implements a register which manages issued and accepted invoices. The main goal of an application is to make tax reduction and tax fraud more difficult.

## Requirements for the functionality:
We assume that companies forward invoices to each other. The company that issues the invoice must deduct VAT from the invoiced amount to the state. Analogously, a company that receives (and pays) an invoice can claim a VAT refund from the state (under certain circumstances). The VAT refund is a weak spot that can be used for tax reduction and tax fraud. Therefore, the task is to implement the core of the system, which will make such tax cuts more difficult.

Issued and received invoices are recorded by the CVATRegister class. Companies must register issued and received invoices. The register matches pairs of corresponding invoices and is able to find unpaired invoices. The invoice can be added to the register as well as canceled (e.g. in the case of incorrectly entered data). The class interface is as follows:

- [X] implicit constructor
- [X] registerCompany ( name ) :
    - The method introduces the entered company into the register. The given name is the official name of the company, this name will be used in exports from the register. The return value is a success (true)/failure (false) indicator. Consider it a failure if a company with the same name already exists in the register. The registry is quite tolerant when comparing business names: it is not case sensitive when comparing, and it doesn't consider redundant spaces when comparing.
- [X] addIssued ( invoice )
    - Method adds the invoice to the registry. This method is called by the company that issued the invoice. The return value is a success (true)/failure (false) flag. 
- [X] addAccepted ( invoice )
    - The method adds the invoice to the register, this method is called by the company that accepted the invoice (buyer). Otherwise, the method behaves the same as addIssued.
- [X] delIssued ( invoice )
    - Method removes the invoice from the register. This method is called by the company that issued the invoice and previously registered it. The return value is a success (true)/failure (false) flag. It is considered an error if the identical invoice was not previously registered using the addIssued method.
- [X] delAccepted ( invoice )
    - Method removes the invoice from the register. This method is called by the company that accepted the invoice and previously registered it. The return value is a success (true)/failure (false) flag. It is considered an error if the identical invoice was not previously registered using the addAccepted method.
- [X] unmatched ( company, sortOpt )
    - The method finds all invoices that relate to the specified company and were not matched (that is, they were registered only with addIssued or only with addAccepted). The method returns a list of these invoices, the invoices will be sorted according to the criteria given by sortOpt. Invoices returned by this method will have the "official" name instead of the company name, i.e. the name that was entered when the company was registered using the registerCompany method. This official name will also be used for sorting.

The CInvoice class represents a single invoice. The interface should be implement:

- [X] constructor ( date, seller, buyer, amount, vat )
    - Initialization of the invoice with the date, name of the seller and buyer company, the invoiced amount and VAT.
- [X] date, seller, buyer, amount, vat
    - Access methods for reading individual invoice components.

The CSortOpt class specifies the sorting criteria. All invoice folders can be used for sorting. 

- [X] implicit constructor
- [X] addKey ( sortBy, ascending )
    - Adds another sorting criterion sortBy, the sorting direction is given by the ascending flag (true = ascending, false = descending). You can sort by:
        - BY_DATE - by invoice date,
        - BY_SELLER - according to the official name of the selling company, sorted regardless of lowercase/uppercase letters,
        - BY_BUYER - according to the official name of the buying company, sorted regardless of lowercase/uppercase letters,
        - BY_AMOUNT - according to the invoiced amount,
        - BY_VAT - according to VAT
