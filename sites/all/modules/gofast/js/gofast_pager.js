/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

jQuery.fn.pager = function (opts) {

  var $this = this;
  var defaults = {
    perPage: 10,
    showPrevNext: false,
    showFirstLast : true,
    hidePageNumbers: false,
    numPageToDisplay : 10,
    isFlex : false
  };

  var settings = jQuery.extend(defaults, opts);

  var listElement = $this;
  var perPage = settings.perPage;
  var pager = jQuery('.pager');


  if(jQuery(listElement).prop("tagName") !== 'TBODY' && jQuery(listElement).prop("tagName") !== 'UL' ){
    // console.log('Pager ERROR : cannot build a pager for this element :'+listElement.prop("tagName"));
  }else{

    var children = listElement.children();

    if (typeof settings.childSelector !== "undefined") {
      children = listElement.find(settings.childSelector);
    }

    if (typeof settings.pagerSelector !== "undefined") {
      pager = jQuery(settings.pagerSelector);
    }

    var numItems = children.size();
    var numPages = Math.ceil(numItems / perPage);
    var nav_class = 'btn btn-icon btn-sm btn-light-primary mr-2 my-1';
    var nb_class = 'btn btn-icon btn-sm border-0 btn-hover-primary mr-2 my-1';

    if(numPages > 1){ // only dispaly pager if nb Pages > 1

      pager.data("curr", 0);

      //clear children
      if(pager.children().size() > 0){
        pager.children().remove();
      }

      if (settings.showFirstLast) {
        jQuery('<li><a href="#" class="' + nav_class + ' first_link" aria-label="First" ><span aria-hidden="false">'+ '<i class="fas fa-angle-double-left"></i>' +'</span></a></li>').appendTo(pager);
      }

      if (settings.showPrevNext) {
        jQuery('<li><a href="#" class="' + nav_class + ' prev_link" aria-label="Previous" ><span aria-hidden="false">'+ '<i class="fas fa-angle-left"></i>' +'</span></a></li>').appendTo(pager);
      }

      var curr = 0;
      while (numPages > curr && (settings.hidePageNumbers === false)) {
        jQuery('<li><a href="#" class="' + nb_class + ' page_link">' + (curr + 1) + '</a></li>').appendTo(pager);
        curr++;
      }

      if (settings.showPrevNext) {
        jQuery('<li><a href="#" class="' + nav_class + ' next_link" aria-label="Next" ><span aria-hidden="false">'+ '<i class="fas fa-angle-right"></i>' +'</span></a></li>').appendTo(pager);
      }

      if (settings.showFirstLast) {
        jQuery('<li><a href="#" class="' + nav_class + ' last_link" aria-label="Last" ><span aria-hidden="false">'+ '<i class="fas fa-angle-double-right"></i>' +'</span></a></li>').appendTo(pager);
      }

    }
    pager.find('.page_link:first').addClass('active');
    pager.find('.prev_link').parent().hide();
    pager.find('.first_link').parent().hide();
    if (numPages <= 1) {
      pager.find('.next_link').parent().hide();
      pager.find('.last_link').parent().hide();
    }
    //pager.children().eq(0).parent().addClass("active");

    //display only a certain nbOfPage
    pageToDisplay = Math.min(settings.numPageToDisplay, numPages );

    pager.find('li .page_link').hide();
    pager.find('li .page_link').slice(0, pageToDisplay).show();

    if(settings.isFlex){
      children.removeClass("d-flex").addClass("d-none");
      children.slice(0, perPage).removeClass("d-none").addClass("d-flex");
    }else{
      children.hide();
      children.slice(0, perPage).show();
    }

    //Event on pager
    pager.find('li .page_link').click(function () {
      var clickedPage = jQuery(this).html().valueOf() - 1;
      goTo(clickedPage);
      return false;
    });
    pager.find('li .prev_link').click(function () {
      previous();
      return false;
    });
    pager.find('li .next_link').click(function () {
      next();
      return false;
    });
    pager.find('li .first_link').click(function () {
      first();
      return false;
    });
    pager.find('li .last_link').click(function () {
      last();
      return false;
    });
  }

  function movePageNumbers(new_page){
    var pageDisplayStart = 0;
    var pageDisplayStop = 0;

    //nb page displayed before/after current page
    pageToDisplay = Math.min(settings.numPageToDisplay, numPages);
    numSidePages = parseInt(pageToDisplay / 2);

    pager.find('li .page_link').hide();
    if( (new_page + 1) <= parseInt(numSidePages) ){
      pageDisplayStart = 0;
      pageDisplayStop = parseInt(0 + pageToDisplay);

    }else if ( (new_page + 1) >= parseInt(numPages - numSidePages) ){
      pageDisplayStart = parseInt(numPages - pageToDisplay);
      pageDisplayStop = numPages;

    }else{
      pageDisplayStart = parseInt(new_page - numSidePages);
      pageDisplayStop = parseInt(new_page + (pageToDisplay - numSidePages) );
    }
    pager.find('li .page_link').slice(pageDisplayStart, pageDisplayStop).show();
  }

  function previous() {
    var goToPage = parseInt(pager.data("curr")) - 1;
    movePageNumbers(parseInt(pager.data("curr")) - 1);
    goTo(goToPage);
  }

  function next() {
    var goToPage = parseInt(pager.data("curr")) + 1;
    movePageNumbers(parseInt(pager.data("curr")) + 1);
    goTo(goToPage);
  }

  function first(){
    goTo(0);
    movePageNumbers(0);
  }

  function last(){
    goTo(numPages-1);
    movePageNumbers(numPages-1);
  }

  function goTo(page) {
    var startAt = page * perPage,
            endOn = startAt + perPage;
    if(settings.isFlex){
      children.removeClass("d-flex").addClass("d-none");
      children.slice(startAt, endOn).removeClass("d-none").addClass("d-flex");
    }else{
      children.css('display', 'none').slice(startAt, endOn).show();
    }

    if (page >= 1) {
      pager.find('.prev_link').parent().show();
      pager.find('.first_link').parent().show();
    }
    else {
      pager.find('.prev_link').parent().hide();
      pager.find('.first_link').parent().hide();
    }

    if (page < (numPages - 1)) {
      pager.find('.next_link').parent().show();
      pager.find('.last_link').parent().show();
    }
    else {
      pager.find('.next_link').parent().hide();
      pager.find('.last_link').parent().hide();
    }

    movePageNumbers(page);

    pager.data("curr", page);
    pager.find('.page_link').removeClass('active')
    pager.children().eq(page+1).children().addClass('active')
  }
};
