
//jQuery namespace
(function ($) {
  Drupal.behaviors.pubzone = {
    attach: function(context, settings) {
      //abstract
      $(".pub-title a").click(function(event) {
        event.preventDefault();
        var extraBlock = event.target.parentElement.parentElement.getElementsByClassName('pub-extras')[0];
        var arrowDown = event.target.getElementsByClassName('glyphicon-chevron-down')[0];
        var arrowUp = event.target.getElementsByClassName('glyphicon-chevron-up')[0];

        if (extraBlock.style.display == 'block') {
          extraBlock.style.display = 'none';
          arrowDown.style.display = 'inline';
          arrowUp.style.display = 'none';

        } else {
          extraBlock.style.display = 'block';
          arrowDown.style.display = 'none';
          arrowUp.style.display = 'inline';
        }
      });
      //bibtex
      $(".pub-meta a.pub-cite").click(function(event) {
        event.preventDefault();
        var extraBlock = event.target.parentElement.parentElement.getElementsByClassName('pub-extras')[0];
        if (extraBlock.style.display == 'block') {
          extraBlock.style.display = 'none';
        } else {
          extraBlock.style.display = 'block';
        }
      });

    }
  };
})(jQuery);
