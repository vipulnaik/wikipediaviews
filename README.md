wikipediaviews
==============

Underlying code of https://wikipediaviews.org with sensitive parts redacted

GitHub URL: https://github.com/vipulnaik/wikipediaviews

WARNING: If you just get the code from GitHub and try running it, it
will fail. You also need to set up the database and add a file at
backend/globalVariables/passwordFile.inc to your backend subdirectory
with the credentials for accessing the database. Configure
passwordFile.inc according to what you currently see in
[backend/globalVariables/dummyPasswordFile.inc](https://github.com/vipulnaik/wikipediaviews/blob/master/backend/globalVariables/dummyPasswordFile.inc).

Instructions for database setup are at
[sql/table-creations.sql](https://github.com/vipulnaik/wikipediaviews/blob/master/sql/table-creations.sql).

## License

This code is released to the public domain. Any referenced or linked
code or libraries used may be subject to their own copyright and
licensing restrictions.

## File structure

All publicly accessible files are in the home directory.

There are three home directory files that offer starting points:

* index.php (Home)

* multiplemonths.php (Multiple months)

* multipleyears.php (Multiple years)

Each file includes these two files from the style subdirectory:

* head.inc controls the header and any site-wide messages

* toggler.inc includes (currently clumsy) JavaScript that allows for
  show/hide features in the HTML display.

In addition, each file includes a corresponding data entry file from
the inputDisplay subdirectory:

* index.php includes onemonthdataentry.inc

* multiplemonths.php includes multiplemonthsdataentry.inc

* multipleyears.php includes multipleyearsdataentry.inc

After we click the submit button on any of the three starting points,
we get sent to a display page. There are three display pages:

* displayviewsforonemonth.php is the target display page from
  onemonthdataentry.inc. In addition to the display, it includes
  multiplemonthsdataentry.inc to facilitate continued data entry (we
  transition automatically from one month to multiple months after the
  first data screen. This is a design decision). So if you submit the
  form again, you go to displayviewsformultiplemonths.php.

* displayviewsformultiplemonths.php is the target display page from
  multiplemonthsdataentry.inc, included in multiplemonths.php. In
  addition to the display, it includes multiplemonthsdataentry.inc.

* displayviewsformultipleyears.php is the target display page for
  multipleyearsdataentry.inc. In addition to the display, it includes
  multipleyearsdataentry.inc to facilitate continued data entry.

All these PHP files also include head.inc and toggler.inc from the
style subdirectory.

## A closer look at the data entry files and the inputDisplay subdirectory

The data entry files themselves include other files, because of common
structure to them. The included files, however, are in the
inputDisplay folder (not publicly accessible over the web). There is a
two-level hierarchy of these files.

* pageListEntry.inc: This file has the code for the text area for
  entering the list of pages, plus instructions on top of that text
  area. It pre-populates the text area with the list of pages from a
  previous GET or POST request if any, otherwise leaves it blank. If
  on a follow-up page, it is collapsed in cases that the pages were
  specified through an alternate page specification method.

  Included in: onemonthdataentry.inc, multiplemonthsdataentry.inc, multipleyearsdataentry.inc

  Associated retrieval file: retrieval/pagelistretrieval.inc

* alternatePageSpecificationMethods.inc: This file has the HTML for
  ways of providing lists of pages without explicitly typing them
  in. There are many methods, each with its own inc file. The decision
  of whether to show or collapse this is based on the form history and
  an automatically generated recommendation.

  Included in: onemonthdataentry.inc, multiplemonthsdataentry.inc, multipleyearsdataentry.inc

  Associated retrieval file: retrieval/pagelistretrieval.inc

* alternateMonthSpecificationMethods.inc: This file has the HTML for
  ways of providing lists of months without having to check boxes.

  Included in: multiplemonthsdataentry.inc

  Associated retrieval file: retrieval/monthlistretrieval.inc

* advancedOptions.inc: This file has the HTML for advanced options,
  mostly relating to how much querying to do and how to display the
  results.

  Included in: onemonthdataentry.inc, multiplemonthsdataentry.inc, multipleyearsdataentry.inc

  Associated retrieval file: retrieval/advancedoptionretrieval.inc

