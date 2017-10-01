"use strict";

jQuery(document).ready(function($) {
    // Document is loaded.  Map each pub to its heading.
    var pubsHeadings = $('.pub, h3');
    var headings = [];
    var lastHeading = null;

    pubsHeadings.each(function() {
        if ($(this).hasClass('pub'))
            headings.push(lastHeading);
        else
            lastHeading = this;
    });

    // Get search from query string, if any
    // XXX Use replaceState to update this when the user searches
    var initialSearch = undefined;
    var qsArgs = location.search.slice(1).split('&');
    for (var i = 0; !initialSearch && i < qsArgs.length; i++) {
        var parts = qsArgs[i].split('=');
        if (decodeURIComponent(parts[0]) === 'search')
            initialSearch = decodeURIComponent(parts[1]);
    }

    // Create publications filter
    function onFilterChange(pubs, matched) {
        // Hide all headings
        for (var i = 0; i < headings.length; i++)
            headings[i].style.display = 'none';

        // Show/hide matched pubs and show headings
        var any = false;
        for (var i = 0; i < pubs.length; i++) {
            pubs[i].style.display = matched[i] ? '' : 'none';
            if (matched[i]) {
                any = true;
                headings[i].style.display = '';
            }
        }

        if (any)
            $('#no-matches').hide();
        else
            $('#no-matches').show();
    }

    function getCategory(obj) {
        // Categories are split by commas, here we need to return an array instead
        return obj.getAttribute('data-category').split(',');
    }

    function getText(item) {
        // this is pretty cool, we can set multiple fields and then search like "key:searchquery"
        //return {'': $(item).text(), 'key': item.getAttribute('data-key')};
        return {'': item.textContent};
    }

    function getYear(item) {
        return {'': item.getAttribute('data-year')};
    }

    new Quickfilter(
        $('.pub'), $('#filter'),
        [new Quickfilter.FreeText('Search', getText,
                                  {initial: initialSearch,
                                   autofocus: false}),
         new Quickfilter.FreeText('Year', getYear,
                                  {initial: initialSearch,
                                   autofocus: false}),
         new Quickfilter.Categorical('Category', getCategory),
         new Quickfilter.Categorical('Type', 'data-type')],
        onFilterChange);
});

function exportBibtex() {
    var outputElts = jQuery('.pub:visible').find('pre');
    var text = [];
    for (var i = 0; i < outputElts.length; i++) {
        text.push(outputElts[i].innerText);
    }
    var blob = new Blob(text, {type: "text/plain;charset=utf-8"});
    saveAs(blob, "references.bib");
}
