/**
 * @fileoverview Custom functionality to apply throughout every adsize. This
 * has a dependency on common.js and utils.js
 */
var custom = (function() {

  /**
   * Classes which our JS hooks into. Add more class names as necessary.
   * @enum
   * @private
   */
  var elementClass_ = {
    item: 'js-item',
    itemPriceS: 'js-item-prices',
    itemPrice: 'js-item-price',
    itemSalePrice: 'js-item-saleprice',
    itemRegularPrice: 'js-item-regularprice',
    itemCta: 'js-item-cta',
    itemBorder: 'js-item-border',
    itemNameOp: 'name-op'
  };

  /**
  * Classes which our JS hooks. 
  * @enum
  * @private
  */
  var elementId_ = {
        arrowPrevious: 'arrow-previous',
    arrowNext: 'arrow-next',
    gpaDataProvider: 'gpa-data-provider'
  };

  /**
   * Initialization. Called from handleAdInitialized on each page.
   */
  function init() {
    utils.log('custom.init()');
    var data = common.getAdData();
    if (!data) return;

    // If you're using the swipe gallery to display feed items.
    initItemsUsingGallery_();

    // If you're NOT using the swipe gallery to display feed items.
    //initItemsWithoutGallery_();


  }
  

  function galleryFrameShown(event) {
    var gallery = common.getGallery();
    var itemsLength = gallery.frameCount;
    var indexFirst = common.getGalleryFrameIndexFirst(event);
    var indexLast = common.getGalleryFrameIndexLast(event);
    var arrowPrevious = utils.getElement(elementId_.arrowPrevious);
    var arrowNext = utils.getElement(elementId_.arrowNext);

    if (itemsLength < 2) {
      utils.showElement(arrowPrevious, false);
      utils.showElement(arrowNext, false);
      return;
    }
    if (indexFirst > 0) {
      arrowPrevious.style.visibility = 'visible';
    } else {
      arrowPrevious.style.visibility = 'hidden';
    }
    if (indexLast < itemsLength - 1) {
      arrowNext.style.visibility = 'visible';

    } else {
      arrowNext.style.visibility = 'hidden';
    }
  }

  /**
   * Find all items used in the swipe gallery and initialize custom behavior.
   * @private
   */
  function initItemsUsingGallery_() {
    var gallery = common.getGallery();

    // Apply settings to each item in the gallery
    var items = gallery.querySelectorAll('.' + elementClass_.item);
    for (var i = 0; i < items.length; i++) {
      var item = items[i];
      initItemDisplay_(item);
    }
  }

  /**
   * Find all items used outside the gallery and initialize custom behavior.
   * @private
   */
  function initItemsWithoutGallery_() {
    // Apply settings to each item
    var items = document.querySelectorAll('.' + elementClass_.item);
    for (var i = 0; i < items.length; i++) {
      var item = items[i];
      initItemDisplay_(item);
    }
  }

  /**
   * Set the display settings for each item.
   * Add any custom functionality you need applied on load.
   * @param {Element} item Item element.
   * @private
   */
  function initItemDisplay_(item) {

    // if you're using sales prices.
    setSalePricesDisplay_(item);

    // Set mouseout.
    itemMouseOut(item);
  }

   /**
   * Set each frame to active on swipegallery autoplay.
   * @param {Event} event Event fired once each frame autoplays.
   */
  function frameAutoplayed(event) {
    var gallery = event.target;
    var index = parseInt(event.detail.id) - 1;

    // Update the current item index.
    common.setCurrentItemIndex(index);

    // Apply mouseover / mouseout to relevant items.
    var items = gallery.querySelectorAll('.' + elementClass_.item);
    for (var i = 0; i < items.length; i++) {
      var item = items[i];
      if (common.isCurrentItemIndex(i)) {
        itemMouseOver(item);
      } else {
        itemMouseOut(item);
      }
    }
  } 

  /**
   * Sets the 3 price elements to display correctly when using sales price.
   * Find your price elements and set into common functionality.
   * @param {Element} item Item element.
   * @private
   */
  function setSalePricesDisplay_(item) {
    // Get reference to each price element.
    var itemPrice = item.querySelector('.' + elementClass_.itemPrice);
    var itemSalePrice = item.querySelector('.' + elementClass_.itemSalePrice);
    var itemRegularPrice = item.querySelector('.' + elementClass_.itemRegularPrice);

    // Sets each item to display correct prices.
    common.displayCorrectPrices(itemPrice, itemSalePrice, itemRegularPrice);
  }

  /**
   * Custom Item Mouse Interactions. Add your own behavior.
   */

  /**
   * Custom Mouseover interaction functionality.
   * @param {Element} item
   */
  function itemMouseOver(item) {


    // Show / hide border:
    var border = item.querySelector('.' + elementClass_.itemBorder);
    if (border) {
      border.style.opacity = 1;
    }
     var nameop = item.querySelector('.' + elementClass_.itemNameOp);
     if(nameop){
        nameop.style.opacity = 1;
     }

    // Show Item CTA button:
    var cta = item.querySelector('.' + elementClass_.itemCta);
    if (cta) {
      var ctaOn = cta.children[1];
      if (ctaOn) utils.showElement(ctaOn, true);
    }
  }

  /**
   * Custom Mouseout interaction functionality.
   * @param {Element} item
   */
  function itemMouseOut(item) {
    // Show / hide border:
    var border = item.querySelector('.' + elementClass_.itemBorder);
    if (border) {
      border.style.opacity = 0;
    }
    var nameop = item.querySelector('.' + elementClass_.itemNameOp);
     if(nameop){
        nameop.style.opacity = 0;
     }
    // Hide Item CTA button:
    var cta = item.querySelector('.' + elementClass_.itemCta);
    if (cta) {
      var ctaOn = cta.children[1];
      if (ctaOn) utils.showElement(ctaOn, false);
    }
  }

    /*
  * Custom transform dynamic data for data validation.
  */
  function transformDynamicData () {
    var dataProvider = document.querySelector('#' + elementId_.gpaDataProvider);
    dataProvider.addDataTransformer(function(dynamicData) {

        var itemAttributes = ['name', 'subTitle', 'description'];
        /**
        * Convert Japanese fullspace to ASCII halfspace.
        */
        if(dynamicData.Product){
          for (var i = 0, l = dynamicData.Product.length; i < l; i++) {

            //name divided 2 part, from and to
            var st1 = dynamicData.Product[i]['name'];
            dynamicData.Product[i]['name']=[];
            var stn1;
            var cst="";
            if(dynamicData.Product[i]['price']){
              dynamicData.Product[i]['price'] = dynamicData.Product[i]['price'].replace("￥","");
              if(dynamicData.Product[i]['price'].indexOf("元起")<0) dynamicData.Product[i]['price']= dynamicData.Product[i]['price']+"<span style='font-size:12px'>元起</span>";
            }
            if(st1 && st1!="" && st1!=null ){
              if(cst && cst!="" && cst!=null ){
                if(st1.indexOf(cst)>-1) stn1 = st1.indexOf(cst);
                else stn1 = st1.length;
              }else stn1 = st1.length;
              //str1 = st1.indexOf(" To ")>st1.indexOf(" to ")?st1.indexOf(" To "):st1.indexOf(" to ");
              if(stn1!=st1.length){
                dynamicData.Product[i]['name'][0] = st1;
                dynamicData.Product[i]['name'][1] = cst + st1.substring(stn1+cst.length,st1.length);
                dynamicData.Product[i]['name'][2] = st1.substring(0,stn1);
                dynamicData.Product[i]['name'][3] = "";
              } 
              else 
              {
                dynamicData.Product[i]['name'][0] = st1;
                dynamicData.Product[i]['name'][1] = st1;
                dynamicData.Product[i]['name'][2] = st1;
                dynamicData.Product[i]['name'][3] = st1;
                //convertLongNameToShortName(dynamicData.Product[i], "name3", nameLength*2);
              }
            }
            else{
              dynamicData.Product[i]['name'][0] = st1;
              dynamicData.Product[i]['name'][1] = st1;
              dynamicData.Product[i]['name'][2] = st1;
              dynamicData.Product[i]['name'][3] = "";
            }

            convertFullspaceToHalfspace(dynamicData.Product[i], itemAttributes);
            priceFormat(dynamicData.Product[i]);
          }
        }
        // Convert headline attributes:
    });
  }

  /**
   * Format price text to avoid unexpected css issues.
   * @param {Object} product Product has product attribute.
   */

  function priceFormat (product) {
    if(!product.price) return;
    product.price = replaceChineseYenSign(product.price);
    product.price = removeCents(product.price);
  }

  /**
   * Replace double byte Chinese Yen sign (￥) to single byte Yen sign (¥).
   * @param {string} price Price attribute pottencially contains Yen sign.
   */
  function replaceChineseYenSign (price) {
    if(!price) return;

    if(price.indexOf("￥") != -1) {
      // Replacing Full Width Yen Sign (\uffe5) with Half Width Yen Sign (\u00a5).
      price = price.replace("\uffe5", "");
      price = price.replace("\u00a5", "");

    }

    return price;
  };

  /**
   * Remove cents where cents = '00'
   * @return {string} with cents removed
   */
  function removeCents (price) {
    if(! price) return;
    var matcher = /(\.|\,)0{2}(?![\d])/;
    return price.replace(matcher, '');
  };

  /**
   * Convert fullspace to ASCII halfspace.
   * @param {Object} item Item whose attributes are checked.
   * @param {Array} attrs Item attributes to check.
   */
  function convertFullspaceToHalfspace (item, attrs) {
    for (var i = 0; i < attrs.length; i++) {
      var attr = attrs[i];
      if(item[attrs[i]]) {
        item[attr] = convert(item[attr]);
      }
    }

    function convert (text) {
      if(text && text.indexOf("　") != -1) {
        text = text.replace(/　/g," ");
      }
      return text;
    }
  };


  return {
    init: init,
    galleryFrameShown: galleryFrameShown,
    frameAutoplayed: frameAutoplayed,
    itemMouseOver: itemMouseOver,
    itemMouseOut: itemMouseOut,
    transformDynamicData: transformDynamicData,
  };

})();
