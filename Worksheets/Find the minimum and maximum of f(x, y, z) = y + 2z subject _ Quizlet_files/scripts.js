var Ad = {
  /*
   Ad properties
  */
  container: document.querySelector("div#container"),
  height: 600,
  width: 300,
  horizontalLayout: false,
  mobileLayout: false,
  boxLayout: false,
  footer: document.getElementsByClassName('footer')[0],
  scale: 1,
  scaleTo: 0.93,
  hasPrice: (myFT.instantAds.price_txt !== "" && myFT.instantAds.percentage_txt === ""),
  hasPercent: (myFT.instantAds.percentage_txt !== "" && myFT.instantAds.price_txt === ""),
  timeline: gsap.timeline(),
  /*
   Method: animate
   Purpose: Animate elements within the DOM using GSAP/CSS
  */
  animate: function () {
      var frames = document.querySelectorAll(".bg-frame"),
      totalAnimationFrames = (myFT.instantAds.frameCount === '2') ? 3 : 1;

    // show ad
    gsap.to('div#container', { duration: 0.25, alpha: 1 }, 0);
    
    // rotate frames + animate background
    for (var i = 0; i < totalAnimationFrames; i++) {
      Ad.animateBackground(frames[i % 2], (i % 2), (i === 2));
    }

    // animate copy
    Ad.timeline.from('div#headline > span', { duration: 1.25, x: -Ad.width, stagger: 0.25 }, 0);
    Ad.timeline.from('div#subheadline > span', { duration: 1.25, x: -Ad.width, stagger: 0.25 }, ">-1");
    if (Ad.hasPercent) {
      Ad.timeline.from('div#percent', { duration: 1, x: -Ad.width }, "<");
    }
    if (Ad.hasPrice)  {
      Ad.timeline.from('div#price', { duration: 1, x: -Ad.width }, "<");
    }

  },

  /*
   Method: animateHeadline
   Purpose: Determine headline animation and apply it to the timeline
  */
  animateBackground: function (frame, index, endFrame) {
    var animationStyle = myFT.instantAds.bgAnimationStyle.split('|')[index];
    var duration = parseInt(myFT.instantAds.animationTiming),
      frameTimeline = gsap.timeline(),
      startingPosition, endingPosition, panLeftEnd = 30, panRightStart = 30;

    if(Ad.mobileLayout) {
      if(animationStyle == 'zoomin' || animationStyle == 'zoomout') {
        Ad.scale = 1.25;
      }
    }
   
    switch (animationStyle) {
      case 'panleft': 
        startingPosition = { 
          x: 0,
          scale: Ad.scale
        };
        endingPosition = {
         x: panLeftEnd,
         duration: duration
        };
        break;
      case 'panright':
        startingPosition = { 
         x: panRightStart,
         scale: Ad.scale
        };
        endingPosition = {
          x: 0,
          duration: duration
        };
        break;
      case 'zoomin': 
        startingPosition = {
          scale: Ad.scale
        }
        endingPosition = {
          scale: Ad.scale * Ad.scaleTo,
          duration: duration
        }
        break;
      case 'zoomout': 
        startingPosition = {
          scale: Ad.scale * Ad.scaleTo
        }
        endingPosition = {
          scale: Ad.scale,
          duration: duration
        }
        break;
    }
    
    frameTimeline.fromTo( frame.querySelector('img'), startingPosition, endingPosition ); 

    // if we have multiple frames
    if (myFT.instantAds.frameCount === '2') {
      Ad.resetFrame(frameTimeline, Number(!index));

      if ( !endFrame ) {
        frameTimeline.to(frame, { duration: 1, x: -Ad.width }, ">");
        frameTimeline.set(frame, { x: 0, zIndex: -3 }, ">");
        frameTimeline.set(frame.querySelector('img'), startingPosition, ">");
        frameTimeline.set(document.querySelectorAll(".bg-frame")[Number(!index)], { zIndex: -1 }, ">");
      }
    }

    Ad.timeline.add(frameTimeline, "-=1");
  },

  /*
   Method: build
   Purpose: Applying dynamic content to the DOM
  */
  build: function () {
    var copy = document.getElementsByClassName('copy')[0],
      headline = document.querySelector("div#headline"),
      subheadline = document.querySelector("div#subheadline"),
      cta = document.querySelector("div#cta"),
      frames = document.querySelectorAll(".bg-frame"),
      frame1Image = document.createElement('img'),
      logoContainer = document.getElementsByClassName('logo-container')[0],
      logo,
      legal = document.querySelector('div#legal');
     


    // headline
    Ad.splitHeadline(headline, myFT.instantAds.headline_txt);
    Ad.styleHeadline(headline, myFT.instantAds.headline_size_hex_xy);

    // subheadline
    Ad.splitHeadline(subheadline, myFT.instantAds.subheadline_txt);
    Ad.styleHeadline(subheadline, myFT.instantAds.subheadline_size_hex_xy);

    // legal
    Ad.splitHeadline(legal, myFT.instantAds.legal_txt);
    Ad.styleHeadline(legal, myFT.instantAds.legal_size_hex_xy);


   

     // percent
     if ( myFT.instantAds.percentage_txt !== "" 
     && myFT.instantAds.price_txt === "" ) {
     var percent = document.querySelector("div#percent");
     percent.style.opacity = 1;
     percent.style.display = "block";

     if(myFT.instantAds.percentage_txt.includes('|')) {

       copy.style.width = '100%';
       percent.style.width = '100%';

       var percentAside = document.createElement('span');
       percentAside.id = 'percent-aside';
       percentAside.style.width = '100%';
       percentAside.style.fontSize = 11 + 'px';
       percentAside.style.lineHeight = 11.3 + 'px';

       percent.style.height = myFT.instantAds.percentage_size_hex_xy.split('|')[0] * .92 + 'px';

       percentAside.innerHTML = myFT.instantAds.percentage_txt.split('|')[1];
       percent.querySelector("span.value").style.display = 'flex';
       percent.querySelector("span.value").innerHTML = myFT.instantAds.percentage_txt.split('|')[0];

       percent.style.display = 'flex';
       percent.style.justifyContent = 'flex-start';
       percent.style.verticalAlign = 'center';
       percent.style.leftAlign = 'center';
      
       percent.appendChild(percentAside);

     } else {
       percent.querySelector("span.value").innerHTML = myFT.instantAds.percentage_txt;
     }
     
     Ad.styleHeadline(percent, myFT.instantAds.percentage_size_hex_xy);

   }

    // price
    if ( myFT.instantAds.price_txt !== ""
      && myFT.instantAds.percentage_txt === "" ) {
      var percent = document.querySelector("div#price");

      percent.style.opacity = 1;
      percent.style.display = "block";
    


      if(myFT.instantAds.price_txt.includes('|')) {

        var priceAside = document.createElement('span');
        
        priceAside.style.display = 'flex';
        priceAside.style.justifyContent = 'flex-start';
        priceAside.style.alignItems = 'center';
        priceAside.style.paddingLeft = '1%';
        
        if(myFT.instantAds.price_txt.split('|')[1].split('<br/>').length < 3) {
          priceAside.style.fontSize = myFT.instantAds.price_size_hex_xy.split('|')[0]/5 + 'px';
          priceAside.style.lineHeight = myFT.instantAds.price_size_hex_xy.split('|')[0]/5 + 'px';
          //transform: translate(0px, -20%); firefox
         } else {
          priceAside.style.fontSize = myFT.instantAds.price_size_hex_xy.split('|')[0]/6 + 'px';
          priceAside.style.lineHeight = myFT.instantAds.price_size_hex_xy.split('|')[0]/6 + 'px';
         }
     
       priceAside.innerHTML = myFT.instantAds.price_txt.split('|')[1];
  
       percent.querySelector("span.value").style.display = 'flex';
       percent.querySelector("span.value").innerHTML = 
       '<span style = "display: flex; line-height: 1.2em; font-size: ' + myFT.instantAds.price_size_hex_xy.split('|')[0]/2 + 'px">' + 
       myFT.instantAds.price_txt.split('|')[0].charAt(0) + '</span>' +
       myFT.instantAds.price_txt.split('|')[0].slice(1);
       
       percent.style.display = 'flex';
       percent.style.justifyContent = 'flex-start';
       percent.style.verticalAlign = 'center';
       percent.style.leftAlign = 'center';
       
       percent.appendChild(priceAside);

      } else {
        percent.querySelector("span.value").innerHTML = myFT.instantAds.price_txt;
      }
      
      Ad.styleHeadline(percent, myFT.instantAds.price_size_hex_xy);
    
    }


     frame1Image.src = myFT.instantAds.F1_background_img;
      frame1Image.addEventListener("load", function() {

        Ad.setupFrameImage(this, frames[0]);

        if (myFT.instantAds.frameCount === '1') {
          Ad.animate();
        } else {
           // background for frame 2, if needed
          var frame2Image = document.createElement('img');
          frame2Image.src = myFT.instantAds.F2_background_img;

          frame2Image.addEventListener("load", function() {
            Ad.setupFrameImage(this, frames[1]);
            Ad.animate();
          });
        }
      });


      Ad.setupPhotoCredits(myFT.instantAds.F1_photoCredits_txt, myFT.instantAds.F1_photoCreditsTxt_size_hex_xy_shadow, frames[0]) ;
      if (myFT.instantAds.frameCount === '2') {
          Ad.setupPhotoCredits(myFT.instantAds.F2_photoCredits_txt, myFT.instantAds.F2_photoCreditsTxt_size_hex_xy_shadow, frames[1]) ;
      }

    
    // cta
    cta.getElementsByTagName('span')[0].innerHTML = myFT.instantAds.cta_txt;
    cta.style.fontSize = myFT.instantAds.ctaTxt_size_hex_hexHov.split("|")[0] + "px";
    cta.style.color = myFT.instantAds.ctaTxt_size_hex_hexHov.split("|")[1];
    cta.style.backgroundColor = myFT.instantAds.ctaBtn_hex_hexHov.split("|")[0];
    if(Ad.mobileLayout) {
       cta.style.right = (Ad.footer.offsetWidth - cta.offsetWidth)/2 + 'px';
     } else if (Ad.boxLayout){
          cta.style.right = '11px';
     } else {
       cta.style.right = (Ad.footer.offsetWidth - cta.offsetWidth)/2 + 'px';
     }
     
    // cta hover animation
    Ad.container.addEventListener("mouseover", function () {
      cta.style.color = myFT.instantAds.ctaTxt_size_hex_hexHov.split("|")[2];
      cta.style.backgroundColor = myFT.instantAds.ctaBtn_hex_hexHov.split("|")[1];
      // only replay if the animation has ended
      if ( Ad.timeline.totalProgress() === 1 ) Ad.timeline.restart();
    });
    Ad.container.addEventListener("mouseout", function () {
      cta.style.color = myFT.instantAds.ctaTxt_size_hex_hexHov.split("|")[1];
      cta.style.backgroundColor = myFT.instantAds.ctaBtn_hex_hexHov.split("|")[0];
    });

    cta.style.transition = '300ms ease-in-out';
    Ad.positionCta(cta);
    Ad.styleFooter(Ad.footer, myFT.instantAds.footer_hex, myFT.instantAds.footer_img);

    // logo
    Ad.createLogoSvgPos(myFT.instantAds.logo_img, logoContainer, Ad.footer.offsetWidth, 13);
    // legal
    Ad.setupLegal(legal, myFT.instantAds.legal_size_hex_xy);

    if (Ad.hasPercent) {
      Ad.shiftCopy('percent', subheadline);
    }
    if (Ad.hasPrice)  {
      Ad.shiftCopy('price', subheadline);
    }

    // clicktag
    myFT.applyClickTag(Ad.container, 1, myFT.instantAds.clickTag1_url);

    //Ad.animate();
  },
  shiftCopy: function(flag, subheadline) {
    // percent
    if(flag === 'percent') {

      var signNode = document.querySelector("div#percent").getElementsByClassName('sign')[0];
      var valueNode = document.querySelector("div#percent").getElementsByClassName('value')[0];
      var percentAside = document.getElementById('percent-aside');
    
      if(myFT.instantAds.percentage_txt.includes('|')) { 

        if(Ad.msieversion()) {

          valueNode.style.display = 'inline-block';
          percentAside.style.position = 'absolute';
          percentAside.style.top = signNode.offsetHeight + 'px';
        
        } else {

          signNode.style.position = "relative";
          signNode.style.display = "flex";
          signNode.style.alignItems = 'top';
          signNode.style.justifyContent = 'top';
          signNode.style.marginBottom = 'auto';
          signNode.style.fontSize = '37%';
          signNode.style.paddingTop = '0.25em';

          percentAside.style.display = 'flex';
          percentAside.style.alignItems = 'flex-end';
          percentAside.style.marginLeft = signNode.offsetWidth * -1 + 'px';

          valueNode.style.paddingRight = valueNode.offsetWidth/20 + 'px';
          }  
        } else {
          // default
          subheadline.style.top = '-.8' + 'em';
          signNode.style.left = valueNode.offsetWidth + (valueNode.offsetWidth*.03) + 'px';
        }
        // price
    } else {
      subheadline.style.top = '-.8' + 'em';
    }
  },
  msieversion: function() {
    var ua = window.navigator.userAgent;
    var msie = ua.indexOf("MSIE ");
    if (msie > 0 || !!navigator.userAgent.match(/Trident.*rv\:11\./))  // If Internet Explorer, return version number
    {
        return true;
    } else  // If another browser, return 0
    {
        return false
    }
},
  positionCta: function(cta) {
  //  cta.style.maxHeight = cta.offsetHeight + 'px';
    if(Ad.boxLayout) {
      var ctaPadding = (Ad.footer.offsetHeight - cta.offsetHeight)/2 + 'px';
      cta.style.top = ctaPadding;
      cta.style.right = ctaPadding;
    } else {
       cta.style.left = (Ad.footer.offsetWidth - cta.offsetWidth)/2 + 'px';
    }
   
  },


  styleFooter: function(footer, bgHex, bgImg) {
    if(bgImg.indexOf("blank") > -1) {
      footer.style.backgroundColor = bgHex;
    } else {
      footer.style.backgroundImage = 'url(' + bgImg + ')';
      footer.style.backgroundSize = 'cover';
  }
  },
  /*
   Method: createLogoSvgPos
   Purpose: Creating logo and positioning SVG cross browser.
  */
  createLogoSvgPos: function(img, container, footerWidth, leftPos) {
    var logo;
    var logoNaturalWidth;
    var logoNaturalHeight;
    var posLeft = leftPos;
    xhr=new XMLHttpRequest();
    xhr.open("GET", img);
    xhr.addEventListener("load", function() {
      // Once the text is available, create an XML parser
      // and parse the text as an SVG image.
      const xmlDoc = new DOMParser().parseFromString(
        this.responseText.trim(), 
        "image/svg+xml"
      );
      var childNodeVal = 0;
      const svgObject = new window.DOMParser().parseFromString(this.response, "text/xml");
      var firstNode = new XMLSerializer().serializeToString(svgObject.childNodes[0]);

      if (!String.prototype.startsWith) {
          String.prototype.startsWith = function(searchString, position){
            return this.substr(position || 0, searchString.length) === searchString;
        };
      }
    
      if(firstNode.startsWith('<!--')) {
        childNodeVal += 1;
      }
      createLogo(svgObject.childNodes[childNodeVal].viewBox.baseVal.width, svgObject.childNodes[childNodeVal].viewBox.baseVal.height);

    });
    xhr.send();

    function createLogo(logoNaturalWidth, logoNaturalHeight) {

      logo = document.createElement('img');
      logo.id = 'logo';
      logo.src = img;
      logo.opacity = 0;

      logo.addEventListener("load", function() {
      
        var ratio = logoNaturalHeight/container.offsetHeight;
        
        if(Ad.boxLayout) {
           if(logoNaturalHeight > 44 && logoNaturalWidth < 2000) {
              posLeft -= Math.abs(container.offsetWidth - logoNaturalWidth/ratio)/2;
            } 
            container.style.left = posLeft + 'px';
        } else if(Ad.horizontalLayout) { 
            container.style.left = (footerWidth - container.offsetWidth)/2 + 'px';
        } else {
            container.style.left = (Ad.width - container.offsetWidth)/2 + 'px';
        }

        container.appendChild(this);
        this.opacity = 1;
      });
    }
  },
  setupLegal: function(legal, config) {
    var legalContents = legal.getElementsByTagName('span')[0];
    var spacer = 4;

    if(Ad.mobileLayout || Ad.width == 728) {
      legal.className += ' rotate';
      legal.style.bottom = (Ad.height - legal.offsetHeight)/2 + 'px';
     
      if(Ad.mobileLayout) {
        spacer = 2;
      }
      legal.style.right = -Math.abs(legalContents.offsetWidth/3) + spacer + 'px';
      legalContents.style.textAlign = 'center';
      legal.style.marginRight = parseInt(config.split('|')[2].split(',')[0])*-1 + 'px';
   
     
    } else if(Ad.boxLayout) {
      // 300x250, 480x320
      legal.style.left = 11 + parseInt(config.split('|')[2].split(',')[0]) + 'px';
      legal.style.bottom = spacer/2 + parseInt(config.split('|')[2].split(',')[1])*-1 + 'px';
      legalContents.style.textAlign = 'left';

      legal.style.marginLeft = parseInt(config.split('|')[2].split(',')[0]) + 'px';
    } else {
      //160x600, 300x600, 970x250, 320x480
     
      legal.style.right = spacer + parseInt(config.split('|')[2].split(',')[0])*-1 + 'px';
      legal.style.bottom = spacer + parseInt(config.split('|')[2].split(',')[1])*-1 + 'px';
      legalContents.style.textAlign = 'right';
      legal.style.marginRight = parseInt(config.split('|')[2].split(',')[0])*-1 + 'px';
   

    }


      legal.style.marginBottom = parseInt(config.split('|')[2].split(',')[1])*-1 + 'px';
     
    
    

 },
setupPhotoCredits: function(txt, config, target) {

  var spacer = 5;
 

  var credits = document.createElement('div');
  credits.className = 'credits';

  Ad.splitHeadline(credits, txt);
  Ad.styleHeadline(credits, config);

  var creditsTxt = credits.getElementsByTagName('span')[0];

  if(Ad.horizontalLayout) {
    credits.style.width = Ad.width - Ad.footer.offsetWidth + 'px';
    credits.style.height = '100%';

    creditsTxt.style.right = Ad.footer.offsetWidth - creditsTxt.offsetWidth + spacer + parseInt(config.split('|')[2].split(',')[0])*-1 + 'px';
    creditsTxt.style.bottom = spacer-1 + parseInt(config.split('|')[2].split(',')[1])*-1  + 'px';

  } else {
    credits.style.width = Ad.width + 'px';  
    credits.style.height = Ad.height - Ad.footer.offsetHeight + 'px';
   


    creditsTxt.style.right = spacer + parseInt(config.split('|')[2].split(',')[0])*-1 + 'px'; 

    if(Ad.width == 480) {
      spacer = 4;
    }

    creditsTxt.style.bottom = (Ad.footer.offsetHeight) + spacer + parseInt(config.split('|')[2].split(',')[1])*-1 + 'px';

  }
 
  target.appendChild(credits);


},
  /*
   Method: setupFrameImage
   Purpose: Positioning animating images.
  */
  setupFrameImage: function(img, target) {
    var resizeFactor;
    if(Ad.horizontalLayout) {
      resizeFactor = parseInt((Ad.width - Ad.footer.offsetWidth) + 60);
    } else {
      resizeFactor = parseInt(Ad.width + 60);
    }
    var ratio = (img.width/resizeFactor);
    img.style.width = resizeFactor + 'px';
    img.style.height = (img.height/ratio) + 'px';
    img.style.opacity = 0;
    target.appendChild(img);

    if(Ad.horizontalLayout) {
      img.style.left = -Math.abs((img.offsetWidth - (Ad.width - Ad.footer.offsetWidth))/2) + "px";
      img.style.top = -Math.abs((img.offsetHeight - Ad.height)/2) + "px";
    } else {
       img.style.left = -Math.abs((img.offsetWidth - Ad.width)/2) + "px";
       img.style.top = -Math.abs((img.offsetHeight - (Ad.height - Ad.footer.offsetHeight))/2) + "px";
    }
    img.style.opacity = 1;
  },

  /*a
   Method: initialize
   Purpose: Adding event listeners for important loading events (images, instantads)
  */
  initialize: function () {
    var elements = [];
    var images = [ 
      myFT.instantAds.F1_background_img, 
      myFT.instantAds.F2_background_img,
      myFT.instantAds.logo_img
    ];
    var imagesLoaded = elements.filter(function (img) {
      return img.complete;
    }).length;

    (window.checkLoaded = function () {
      if ( imagesLoaded === images.length 
        && myFT.instantAdsLoaded ) {
        Ad.build();
      }
    })();

    images.forEach(function (path) {
      var img = new Image();
      img.src = path;
      elements.push(img);
      return (img.onload = function () {
        imagesLoaded++;
        checkLoaded();
      });
    });
  },

  /*
   Method: splitHeadline
   Purpose: Splitting headlines into their own elements because of staggered animation
  */
  splitHeadline: function (parent, content) {

    var split = content.split("|");

    for (let i = 0; i < split.length; i++) {
      var line = split[i];
      var element = document.createElement("span");

      element.innerHTML = line;
      parent.appendChild(element);
    }
  },

  /*
   Method: styleHeadline
   Purpose: Applying common dynamic styling to elements
  */
  styleHeadline: function (element, styles) {

  
    var split = styles.split("|");
    var marginTop = split[2].split(",")[1];
    element.style.color = split[1];
    element.style.fontSize = split[0] + "px";
    element.style.marginLeft = split[2].split(",")[0];

    if(split[3] ==='true') {
      element.style.textShadow = '0px 1px 1px rgba(0, 0, 0, 0.4)';
    };
    element.style.marginTop = marginTop + 'px';
  },

  /*
   Method: resetFrame
   Purpose: Applying center positioning to final image
  */
  resetFrame: function (timeline, index) {
    var element = document.querySelectorAll(".bg-frame")[index].querySelector('img');

    switch (myFT.instantAds.bgAnimationStyle.split('|')[index]) {
      case 'panleft':
      case 'panright':
        timeline.set(element, { 
          x: 0, 
          scale: 1 
        }, ">");
        break;
      case 'zoomin':
      case 'zoomout':
        timeline.set(element, {
          scale: 0.92
        }, ">");
        break;
    }
  },
};

document.addEventListener("DOMContentLoaded", Ad.initialize);

if (!String.prototype.includes) {
  String.prototype.includes = function(search, start) {
    'use strict';

    if (search instanceof RegExp) {
      throw TypeError('first argument must not be a RegExp');
    }
    if (start === undefined) { start = 0; }
    return this.indexOf(search, start) !== -1;
  };
}  