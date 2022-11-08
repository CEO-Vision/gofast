/* global Gofast, Drupal */

(function ($, Gofast, Drupal) {
  'use strict';

  Drupal.behaviors.gofastCalendar = {
    attach: function(context, settings){
      $('.date-views-pager').find('.icon-after').on('click', function () {
        //remove tooltip
        $('.tooltip').each(function(key, elt){
          $(elt).remove();
        });
      });

      $('.date-views-pager').find('.icon-before').on('click', function () {
        //remove tooltip
        $('.tooltip').each(function(key, elt){
          $(elt).remove();
        });
      });
    }

  };

    Drupal.behaviors.gofastCalendar_popover = {
        attach: function(context, settings){
            if (typeof $('.popup_calendar:not(.calendar_popover-processed)',context).popover == "undefined" || Gofast._settings.isMobile) {
                return;
            }

            $('.popup_calendar:not(.calendar_popover-processed)',context).addClass('calendar_popover-processed').popover({
                content:function() {
                    var my_id = $(this).attr("id");
                    if (my_id !== ""){
                        return $('#window_popup_calendar_'+my_id).html();
                    }
                },
                html:true,
                placement:'bottom',
                trigger:'hover'
            });
        }
    };


    Drupal.behaviors.InitCalendar = {
      attach: function(context, settings){
        var KTCalendarBasic = function () {

          let initPopover = function(el, event) {
            el.data('placement', 'top');
            el.data('content', getPopOverContent(event))
            el.data('html', true)
            el.attr('title', event.title)
            var skin = el.data('skin') ? 'popover-' + el.data('skin') : '';
            var triggerValue = el.data('trigger') ? el.data('trigger') : 'hover';
            const {user} = event.extendedProps

            el.popover({
                trigger: triggerValue,
                template: '<div class="popover ' + skin + ' p-0" role="tooltip"><div class="arrow"></div><div class="popover-header p-2 text-truncate"></div><div class="popover-body p-2"></div><div class="popover-footer d-flex p-2 d-flex font-size-sm"> <span class="text-muted mr-4">' + Drupal.t('Created by') + ':</span> <div class="d-flex"> <div class="symbol symbol-circle symbol-20 mr-2 d-flex align-items-center"> <img alt="Pic" style="max-width: 15px; height: 15px;" src="' + user.picture + '"/> </div> <div class="text-muted">' + user.firstname + ' ' + user.lastname + '</div> </div></div></div>',
            });
          }

          let getPopOverContent = (event) => {
              let description = Drupal.t("No description");
              switch(event.extendedProps.type){
                  case 'conference':
                      return event.extendedProps.description.und ? event.extendedProps.description.und[0].value : description;
                  default:
                      return description;
              }
          }


          return {
            //main function to initiate the module
            init: function () {
              var User = Gofast.get("user");
              var user_language = User.language;

              var calendarEl = document.getElementById('kt_calendar');
              var calendar = new FullCalendar.Calendar(calendarEl, {

                buttonText : {
                  today:    Drupal.t('today'),
                  month:    Drupal.t('month'),
                  week:     Drupal.t('week'),
                  day:      Drupal.t('day'),
                  list:     Drupal.t('list'),
                },


                allDayText: Drupal.t('all-day'),
                locale: user_language,
                plugins: ['bootstr  ap', 'interaction', 'dayGrid', 'timeGrid', 'list','locales'],
                isRTL: KTUtil.isRTL(),

                header: {
                  left: 'prev,next today',
                  center: 'title',
                  right: 'dayGridMonth,timeGridWeek,timeGridDay'
                },

                height: 'parent',
                aspectRatio: 3, // see: https://fullcalendar.io/docs/aspectRatio

                nowIndicator: true,
                now: Date.now(), // just for demo

                defaultView: 'timeGridWeek',

                editable: false,
                eventLimit: true, // allow "more" link when too many events
                navLinks: true,
                events: function(fetchInfo, successCallback, failureCallback) {
                  Gofast.getCalendarEvents(fetchInfo, calendarEl.dataset.id, successCallback, failureCallback);
                },
                eventRender: function(info) {

                  let element = $(info.el);
                  let content = element.find('.fc-content')

                  content.addClass('p-2')
                  content.find('.fc-time').hide()
                  element.find('.fc-title').addClass('font-weight-bolder');
                  element.attr('href', '/node/' + info.event.extendedProps.nid);

                  if(info.event.extendedProps && info.event.extendedProps.type){

                      if(info.event.extendedProps.type == 'conference'){
                          let start = new Date(info.event.start)
                          let end = new Date(info.event.end)
                          let startHour = start.toLocaleTimeString([], {hour: '2-digit', minute: '2-digit'})
                          let endHour = end.toLocaleTimeString([], {hour: '2-digit', minute: '2-digit'})
                          let el = "<div class=\"text-dark-50 mt-1 font-weight-bold\">" + startHour + " - " + endHour + "</div>";
                          element.find('.fc-content').append(el);
                          let icon = '<i class="fas fa-video icon-nm mr-2"></i>';
                          element.find('.fc-title').prepend(icon);
                      }

                      if(info.event.extendedProps.type == 'task' || info.event.extendedProps.type == 'kanban'){
                          if(info.event.extendedProps.icon){
                            let icon = '<i class="fab fa-trello icon-nm mr-2"></i>'
                            element.find('.fc-title').prepend(icon)
                          }
                      }

                      if(info.event.extendedProps.type == 'alfresco_item' || info.event.extendedProps.type == 'article'){
                          let icon = "";
                          if(info.event.extendedProps.icon){
                            icon = '<i class="far fa-file-'+info.event.extendedProps.icon+' icon-nm mr-2"></i>'
                          } else {
                            icon = '<i class="far fa-file icon-nm mr-2"></i>'
                          }
                          element.find('.fc-title').prepend(icon)
                      }

                      initPopover(element, info.event);
                      if (element.hasClass('fc-time-grid-event')) {
                          element.addClass('scroll', 'scroll-pull');
                          element.attr('data-scroll', 'true')
                          element.attr('data-wheel-propagation', 'true')
                          let desc = typeof info.event.extendedProps.description.und !== "undefined" ? info.event.extendedProps.description.und[0].value : Drupal.t("No description");
                          element.find('.fc-title').append("<div class=\"fc-description\"></div>");
                          element.find('.fc-description').css({whiteSpace: 'nowrap', overflow: 'hidden', textOverflow: 'ellipsis'}).append(desc);
                      } else if (element.find('.fc-list-item-title').length !== 0) {
                          element.find('.fc-list-item-title').append('<div class="fc-description">' + info.event.title + '</div>');
                      }
                  }

                },
                datesRender: function({view, el}){
                  if(view.type == 'dayGridMonth'){
                      let days = el.querySelectorAll('.fc-day-top')                     
                      if(days && days.length > 0) {
                          days.forEach((day) => {
                            let currentDate = day.dataset.date
                            let nodeId = calendarEl.dataset.id
                            let link = document.createElement('a')
                            link.className = 'btn btn-link-primary'
                            link.innerHTML = '+'
                            link.href = '/node/add/conference?deadline='+currentDate+'&gid='+nodeId
                            day.prepend(link)
                          })
                      }
                  }else{
                          let days = el.querySelectorAll('.fc-day-header')
                            console.log("calendar add");
                             console.log(days);
                            if(days && days.length > 0) {
                                days.forEach((day) => {
                                  let currentDate = day.dataset.date
                                  let nodeId = calendarEl.dataset.id
                                  let link = document.createElement('a')
                                  link.className = 'btn btn-link-primary'
                                  //link.innerHTML = '<span style="margin-left:10px;font-weight:bold;font-size:xx-large"> +</span>'
                                  link.innerHTML = '<span class="fa fa-plus" style="color:#3699ff;margin-left:10px;"></span>';
                                  link.href = '/node/add/conference?deadline='+currentDate+'&gid='+nodeId
                                  let br = document.createElement('br')
                                  day.append(br);
                                  day.append(link);
                                })
                        }
                    }
              }
              });
              calendar.on("datesRender", function(info) {
                const events = calendar.getEvents();
                const activeStart = info.view.activeStart;
                const activeEnd = info.view.activeEnd;
                const currentEvents = events.filter(event => event.start > activeStart && event.end < activeEnd);
                const $calendarTitleElement = $(".fc-toolbar .fc-center > *:last-child");
                $calendarTitleElement.addClass("d-flex").append("<span class='ml-3 label label-inline font-weight-bold label-dark'>"
                + currentEvents.length
                + " "
                + (currentEvents.length > 1 ? Drupal.t('events') : Drupal.t('event'))
                + "</span>");
              });
              calendar.render();

              $('#tab_ogcalendar').on('shown.bs.tab', function (e) {
                // update size of calendar when the tab is showed
                calendar.updateSize();
              })
            }
          };
        }();

        $('#kt_calendar:not(.calendar-processed)', context).addClass('calendar-processed').each(function(){
          KTCalendarBasic.init();
        });
      }
    }

  Gofast.getCalendarEvents = function (fetchInfo, nid, successCallback, failureCallback) {
    var data = {
      nid: nid,
      fetchInfo: fetchInfo
    };
    $.ajax({
      type: "GET",
      url: window.origin + "/calendar/get_calendar",
      data: data,
      async: false,
      success: function (data) {
        successCallback(data);
      },
      dataType: 'json'
    });
  }

})(jQuery, Gofast, Drupal);
