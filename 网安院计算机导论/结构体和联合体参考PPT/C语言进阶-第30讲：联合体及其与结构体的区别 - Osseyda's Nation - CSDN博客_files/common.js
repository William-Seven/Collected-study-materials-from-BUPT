/**
 * @fileoverview Common functionality required to serve in AdWords.
 * This has a dependency on utils.js.
 */
var common = (function() {

  /**
   * Element Attributes.
   * @enum {string}
   * @private
   */
  var elementAttr_ = {
    gwdRepeatIndex: 'gwd-repeat-index',
    dataProductIndex: 'data-product-index',
    numFramesToDisplay: 'num-frames-to-display',
    frameSnapInterval: 'frame-snap-interval',
    dataGwdWidth: 'data-gwd-width',
    dataGwdHeight: 'data-gwd-height'
  };

  /**
   * Element IDs.
   * @enum {string}
   * @private
   */
  var elementId_ = {
    page1: 'page1',
    pageDeck: 'pagedeck',
    gpaDataProvider: 'gpa-data-provider'
  };

  /**
   * Element Classes.
   * @enum {string}
   * @private
   */
  var elementClass_ = {
    item: 'js-item'
  };

  /**
   * Feed specs. Used to determine feed types used.
   * @enum {boolean}
   */
  var feedSpecs_ = {
    includeRatings: false,
    includeSalePrices: false,
    includeSalePercentDiscounts: false
  };

  /**
   * @type {number}
   * @const
   */
  var DEFAULT_TIMEOUT_DUR = 100;

  /**
   * INITIALIZATION
   */

  /**
   * Initialization. Called from {@code handleAdInitialized} on each page.
   */
  function init() {
    getAdData();
    utils.log('adData: ', adData_);
    if (!adData_) {
      utils.warn('adData_ unavailable / no feed loaded.');
      return;
    }

    verifyFeedSpecs_();
    hideEmptyImages_();

    getPageSize();
  }

  /** @private */
  var adData_;

  /**
   * Get access to Dynamic Data Attributes.
   * @return {Object} Dynamic ad data.
   */
  function getAdData() {
    adData_ = document.getElementById(elementId_.gpaDataProvider).getData();
    return adData_;
  }

  /**
   * Return object containing page width and height.
   * @return {Object} Page size.
   */
  function getPageSize() {
    var page = document.getElementById(elementId_.page1);
    var size = {
      width: page.getAttribute(elementAttr_.dataGwdWidth),
      height: page.getAttribute(elementAttr_.dataGwdHeight)
    };
    return size;
  }

  /**
   * Hide all images whose source is not defined.
   * @private
   */
  function hideEmptyImages_() {
    var imgs = document.getElementsByTagName('img');
    for (var i = 0, numImages = imgs.length; i < numImages; i++) {
      if (imgs[i].getAttribute('source') == 'undefined') {
        imgs[i].style.visibility = 'hidden';
      }
    }
  }

  /**
   * Verify the feed specs.
   * Required to determine which feeds and use cases are used.
   * @private
   */
  function verifyFeedSpecs_() {
    var items = adData_.Product;
    for (var i = 0; i < items.length; i++) {
      var item = items[i];
      if (item.rating) {
        feedSpecs_.includeRatings = true;
      }
      if (item.salePrice) {
        feedSpecs_.includeSalePrices = true;
      }
      if (item.salePercentDiscount) {
        feedSpecs_.includeSalePercentDiscounts = true;
      }
    }
    utils.log('feedSpecs: ', feedSpecs_);
  }

  /**
   * GALLERY USER ACTIONS
   */

  /**
   * @type {Element}
   * @private
   **/
  var gallery_;

  /**
   * Set an internal reference to the swipegallery and verify it exists.
   * @param {string} id Element ID.
   */
  function setGallery(id) {
    gallery_ = utils.getElement(id);
    utils.log('gallery id: ' + id, gallery_);
  }

  /**
   * Get the gallery reference while check it exists.
   * @return {Element}
   */
  function getGallery() {
    if (!checkGallery()) {
      return;
    }
    return gallery_;
  }

  /**
   * Handle Swipegallery All Frames Viewed event.
   * @param {Event} event Swipegallery frame event.
   */
  function galleryAllFramesViewed(event) {
    logGalleryFrameAction_(event);
  }

  /**
   * Handle Swipegallery Frame Activated event.
   * @param {Event} event Swipegallery frame event.
   */
  function galleryFrameActivated(event) {
    logGalleryFrameAction_(event);
    if (!adData_) return;
    setCurrentItemIndex(getGalleryFrameIndexFirst(event));
  }

  /**
   * Handle Swipegallery Frame Shown event.
   * @param {Event} event Swipegallery frame event.
   */
  function galleryFrameShown(event) {
    logGalleryFrameAction_(event);
    if (!adData_) return;
    setCurrentItemIndex(getGalleryFrameIndexFirst(event));
  }

  /**
   * Find the number of simultaneously visible frames displayed per page. Refers to the
   * num-frames-to-display Swipegallery attribute. If attribute has not been set defaults to 1.
   * @param {Element} gallery Swipegallery.
   * @return {number} Number of visible frames per page.
   */
  function galleryNumFramesPerPage(gallery) {
    var frames = gallery.getAttribute(elementAttr_.numFramesToDisplay);
    if (frames === null) frames = 1;
    return Number(frames);
  }

  /**
   * Find the number of frames each swipe moves. Refers to the
   * frame-snap-interval Swipegallery attribute. If attribute has not been set defaults to 1.
   * @param {Element} gallery Swipegallery.
   * @return {number} Number of frames per page swipe.
   */
  function galleryNumFramesPerSwipe(gallery) {
    var frames = gallery.getAttribute(elementAttr_.frameSnapInterval);
    if (frames === null) frames = 1;
    return Number(frames);
  }

  /**
   * Get the Swipegallery first visible frame index.
   * @param {Event} event Swipegallery frame event.
   * @return {number} Index of first visible frame.
   */
  function getGalleryFrameIndexFirst(event) {
    if (event.detail && event.detail.id) {
      var frameIndexCenter = event.detail.id - 1;
      var framesPerPage = galleryNumFramesPerPage(event.target);
      var frameIndexFirst;
      if (framesPerPage % 2 === 0) {
        frameIndexFirst = frameIndexCenter + 1 - framesPerPage / 2;
      } else {
        frameIndexFirst = frameIndexCenter - Math.floor(framesPerPage / 2);
      }
      frameIndexFirst = Math.max(frameIndexFirst, 0);
      return frameIndexFirst;
    }
    return 0;
  }

  /**
   * Get the Swipegallery last visible frame index.
   * @param {Event} event Swipegallery frame event.
   * @return {number} Index of last visible frame.
   */
  function getGalleryFrameIndexLast(event) {
    var frameIndexLast = getGalleryFrameIndexFirst(event) + galleryNumFramesPerPage(event.target) - 1;
    if (adData_ && adData_.Product) {
      frameIndexLast = Math.min(frameIndexLast, adData_.Product.length - 1);
    }
    return frameIndexLast;
  }

  /**
   * Logs current gallery frame action, including reference to frame index.
   * @param {Event} event Swipegallery frame event.
   * @private
   */
  function logGalleryFrameAction_(event) {
    utils.log('gallery ' + event.type + ' ' + getGalleryFrameIndexFirst(event));
  }

  /**
   * Go to a specific frame in gwd-swipegallery.
   * @param {number} index Frame index to go to.
   */
  function galleryGoToFrame(index) {
    if (!checkGallery()) {
      return;
    }
    gallery_.goToFrame(index);
  }

  /**
   * Set the gwd-swipegallery to rotate once.
   * @param {number} duration Total duration for single rotation in ms.
   */
  function galleryAutoRotate(duration) {
    if (!checkGallery()) {
      return;
    }
    setTimeout(function() {
      gallery_.rotateOnce(duration, 'forwards');
    }, DEFAULT_TIMEOUT_DUR);
  }

  /**
   * Stops the gwd-swipegallery rotation.
   */
  function galleryStopRotation() {
    if (!checkGallery()) {
      return;
    }
    gallery_.stopRotation();
  }

  /**
   * Check whether the gwd-swipegallery ID has been set.
   * @return {Boolean}
   */
  function checkGallery() {
    if (!gallery_) {
      utils.warn('gallery undefined. call common.setGallery() from' +
        ' handleWebComponentsReady(), passing in the swipe-gallery ID.');
      return false;
    }
    return true;
  }

  /**
   * ITEM INTERACTION
   */

  /**
   * Determine whether element contains an item. Refers to the necessary
   * 'js-item' class.
   * @param {Element} el Element to check.
   * @return {boolean}
   * @private
   */
  function elementIsItem_(el) {
    return el.classList.contains(elementClass_.item);
  }

  /**
   * Find the item element by traversing the element and returning the nearest.
   * @param {Element} el Element to check.
   * @return {Element} The element which is considered a feed item.
   */
  function getItemElement(el) {
    var item = utils.closestElement(el, elementIsItem_);
    return item;
  }

  /**
   * Get the index of the item. Checks either of 2 attributes:
   * a) data-product-index, which is added manually, or
   * b) gwd-repeat-index, which is added for each repeated item (Aug 2015 release).
   * @param {Element} item Item element.
   * @return {?number} Index of the repeated item.
   */
  function getItemIndex(item) {
    var index = item.getAttribute(elementAttr_.gwdRepeatIndex);
    if (index === null || isNaN(index)) {
      index = item.getAttribute(elementAttr_.dataProductIndex);
    }
    if (index === null || isNaN(index)) {
      utils.warn('Item element has no reference to index');
    }
    return index;
  }

  /**
   * Mouseover interaction handler, includes necessary interaction tracking.
   * @param {Event} event Mouseover Event.
   */
  function itemMouseover(event) {
    itemInteracted(true);
    var item = getItemElement(event.target);
    itemActive(item, true);
  }

  /**
   * Mouseout interaction handler, includes necessary interaction tracking.
   * @param {Event} event Mouseout Event.
   */
  function itemMouseout(event) {
    itemInteracted(false);
    var item = getItemElement(event.target);
    itemActive(item, false);
  }

  /**
   * Setting the item to active / inactive. Item is referenced via the
   * 'js-item' class. Item's index is referenced via the 'data-product-index'
   * attribute.
   * @param {Element} item Item element.
   * @param {boolean} isActive Whether the item is active.
   */
  function itemActive(item, isActive) {
    validateItem(item);
    if (!item) return;
    if (isActive) {
      var index = getItemIndex(item);
      if (index !== null) {
        setCurrentItemIndex(index);
      }
      // custom interaction:
      if (custom && custom.itemMouseOver) {
        custom.itemMouseOver(item);
      }
    } else {
      // custom interaction:
      if (custom && custom.itemMouseOut) {
        custom.itemMouseOut(item);
      }
    }
  }



  /**
   * Validate the item.
   * Convenience method to warn developer when item is not available.
   * @param {Element} item Item element.
   */
  function validateItem(item) {
    if (!item) {
      utils.warn('gallery item not found: add "js-item" class to gallery' +
        ' group element');
    }
  }

  /**
   * ITEM NAVIGATION
   */

  /**
   * @type {number}
   * @private
   */
  var currentItemIndex_ = 0;

  /**
   * Sets the current feed item index.
   * @param {number} index Number to set as the current index.
   */
  function setCurrentItemIndex(index) {
    currentItemIndex_ = index;
    utils.log('currentItemIndex: ' + currentItemIndex_);
  }

  /**
   * Get the current feed item index.
   * @return {number} Current item index.
   */
  function getCurrentItemIndex() {
    return currentItemIndex_;
  }

  /**
   * Whether the index matches the current item index.
   * @param {number} index
   * @return {Boolean}
   */
  function isCurrentItemIndex(index) {
    return currentItemIndex_ == index;
  }

  /**
   * Increments the current feed item index.
   */
  function setCurrentItemNext() {
    var items = adData_.Product;
    var index = currentItemIndex_ < items.length - 1 ? currentItemIndex_ + 1 : 0;
    setCurrentItemIndex(index);
  }

  /**
   * Decrements the current feed item index.
   */
  function setCurrentItemPrevious() {
    var items = adData_.Product;
    var index = currentItemIndex_ > 0 ? currentItemIndex_ - 1 : items.length - 1;
    setCurrentItemIndex(index);
  }

  /**
   * EXIT FUNCTIONALITY
   */

  /**
   * @type {boolean}
   * @private
   */
  var isExitOnItem_ = false;

  /**
   * Handler for when a user interacts with a feed item element.
   * @param {boolean} state Whether the user is currently interacting.
   */
  function itemInteracted(state) {
    isExitOnItem_ = state;
    if (gallery_) galleryStopRotation();
  }

  /**
   * Determines behavior of the exit click. Whether the ad's settings require
   * every click exists to the current interacted item, or only when the
   * current clicks on an item.
   * @return {boolean}
   */
  function isProductClickOnly() {
    var adData_ = adData_ ? adData_ : getAdData();
    return (adData_ && adData_.Headline && adData_.Headline.productClickOnly &&
      adData_.Headline.productClickOnly.toLowerCase() == 'true');
  }

  /**
   * Exit to either the feed item url or default url depending on where the
   * user clicks, and value of isProductClickOnly.
   * This is based on productClickOnly attribute value.
   */
  function exitAuto() {
    if (isExitOnItem_ || isProductClickOnly()) {
      exitToItem();
    } else {
      exitToDefault();
    }
  }

  /**
   * Exit to the feed item url only.
   */
  function exitToItem() {
    var exitId = 'Product_' + currentItemIndex_ + '_url';
    utils.log('Enabler.exit item: ' + exitId);
    Enabler.exit(exitId);
  }

  /**
   * Exit to the default url only.
   */
  function exitToDefault() {
    utils.log('Enabler.exit default');
    Enabler.exit('default');
  }

  /**
   * PRICES
   */

  /**
   * Sets the correct display of each price element to show sales prices.
   * @param {element} defaultPrice Default price (displays alone).
   * @param {element} salePrice Sale price (displays with regular price).
   * @param {element} regularPrice Regular price (displays with sale price).
   */
  function displayCorrectPrices(defaultPrice, salePrice, regularPrice) {
    var priceValues = {
      defaultPrice: defaultPrice && defaultPrice.textContent || null,
      salePrice: salePrice && salePrice.textContent || null,
      regularPrice: regularPrice && regularPrice.textContent || null
    };
    utils.log('priceValues: ', priceValues);

    if (isSalePriceEnabled_(priceValues)) {
      showSalePrice(true, defaultPrice, salePrice, regularPrice);
    } else {
      showSalePrice(false, defaultPrice, salePrice, regularPrice);
    }
  }

  /**
   * Show or hide the sales prices.
   * @param {Boolean} state
   * @param {?element} defaultPrice Default price (displays alone).
   * @param {?element} salePrice Sale price (displays with regular price).
   * @param {?element} regularPrice Regular price (displays with sale price).
   */
  function showSalePrice(state, defaultPrice, salePrice, regularPrice) {
    utils.showElement(defaultPrice, !state);
    utils.showElement(salePrice, state);
    utils.showElement(regularPrice, state);
  }

  /**
   * Determines whether the item contains a valid sale price for Retail.
   * @param {Object} item Item object that contains prices.
   * @return {boolean} Whether a valid sale price exists.
   * @private
   */
  function isSalePriceEnabled_(item) {
    var isEnabled = item.salePrice && item.regularPrice &&
      !utils.isEmptyString(item.salePrice) &&
      !utils.isEmptyString(item.regularPrice) &&
      utils.stringValuesAreUnique(item.salePrice, item.regularPrice);
    return isEnabled;
  }

  return {
    init: init,
    getAdData: getAdData,
    getPageSize: getPageSize,
    setCurrentItemIndex: setCurrentItemIndex,
    getCurrentItemIndex: getCurrentItemIndex,
    isCurrentItemIndex: isCurrentItemIndex,
    setCurrentItemNext: setCurrentItemNext,
    setCurrentItemPrevious: setCurrentItemPrevious,
    getItemElement: getItemElement,
    getItemIndex: getItemIndex,
    itemInteracted: itemInteracted,
    setGallery: setGallery,
    getGallery: getGallery,
    galleryFrameShown: galleryFrameShown,
    galleryFrameActivated: galleryFrameActivated,
    galleryAllFramesViewed: galleryAllFramesViewed,
    galleryNumFramesPerPage: galleryNumFramesPerPage,
    galleryNumFramesPerSwipe: galleryNumFramesPerSwipe,
    getGalleryFrameIndexFirst: getGalleryFrameIndexFirst,
    getGalleryFrameIndexLast: getGalleryFrameIndexLast,
    itemMouseover: itemMouseover,
    itemMouseout: itemMouseout,
    galleryGoToFrame: galleryGoToFrame,
    galleryAutoRotate: galleryAutoRotate,
    galleryStopRotation: galleryStopRotation,
    isProductClickOnly: isProductClickOnly,
    exitAuto: exitAuto,
    exitToItem: exitToItem,
    exitToDefault: exitToDefault,
    displayCorrectPrices: displayCorrectPrices,
    showSalePrice: showSalePrice
  };

})();
