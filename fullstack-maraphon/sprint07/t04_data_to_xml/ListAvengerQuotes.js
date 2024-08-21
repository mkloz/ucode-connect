const fs = require('fs');
const xml2js = require('xml2js');
const path = require('path');
const XML_FILE = path.join(__dirname, 'avenger_quote.xml');

class ListAvengerQuotes {
  constructor() {
    this.quotes = [];
  }

  addQuote(quote) {
    this.quotes.push(quote);
  }

  toXML() {
    const builder = new xml2js.Builder({
      rootName: 'quotes',
    });
    const xml = builder.buildObject(this.quotes.map((quote) => ({ quote })));
    fs.writeFileSync(XML_FILE, xml);
  }

  fromXML() {
    const xml = fs.readFileSync(XML_FILE, 'utf-8');
    xml2js.parseString(
      xml,
      {
        explicitArray: false,
      },
      (err, result) => {
        if (err) {
          console.error('Error parsing XML:', err);
          return;
        }
        this.quotes = result ? result.quotes.quote : [];
      },
    );
  }
}

module.exports = { ListAvengerQuotes };
