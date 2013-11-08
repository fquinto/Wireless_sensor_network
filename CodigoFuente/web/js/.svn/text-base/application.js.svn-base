!function ($) {
  $(function(){

    $('.dropdown-toggle').dropdown()
    
	// position static twipsies for components page
	    if ($(".twipsies a").length) {
	      $(window).on('load resize', function () {
	        $(".twipsies a").each(function () {
	          $(this)
	            .tooltip({
	              placement: $(this).attr('title')
	            , trigger: 'manual'
	            })
	            .tooltip('show')
	          })
	      })
	    }

	    // add tipsies to grid for scaffolding
	    if ($('#grid-system').length) {
	      $('#grid-system').tooltip({
	          selector: '.show-grid > div'
	        , title: function () { return $(this).width() + 'px' }
	      })
	    }

	    // fix sub nav on scroll
	    var $win = $(window)
	      , $nav = $('.subnav')
	      , navTop = $('.subnav').length && $('.subnav').offset().top - 40
	      , isFixed = 0
/*
	    processScroll()

	    $win.on('scroll', processScroll)

	    function processScroll() {
	      var i, scrollTop = $win.scrollTop()
	      if (scrollTop >= navTop && !isFixed) {
	        isFixed = 1
	        $nav.addClass('subnav-fixed')
	      } else if (scrollTop <= navTop && isFixed) {
	        isFixed = 0
	        $nav.removeClass('subnav-fixed')
	      }
	    }*/
	  
    // tooltip demo
    /*
    $('.tooltip-demo.well').tooltip({
      selector: "a[rel=tooltip]"
    })

    $('.tooltip-test').tooltip()
    $('.popover-test').popover()

    // popover demo
    $("a[rel=popover]")
      .popover()
      .click(function(e) {
        e.preventDefault()
      })
*/
    // button state demo
    $('#fat-btn')
      .click(function () {
        var btn = $(this)
        btn.button('loading')
        setTimeout(function () {
          btn.button('reset')
        }, 3000)
      })

  })
}(window.jQuery)