
//jQuery namespace
(function ($) {
  Drupal.behaviors.pubzone = {
    attach: function(context, settings) {
      $(".pub-title a").click(function(event) {
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
