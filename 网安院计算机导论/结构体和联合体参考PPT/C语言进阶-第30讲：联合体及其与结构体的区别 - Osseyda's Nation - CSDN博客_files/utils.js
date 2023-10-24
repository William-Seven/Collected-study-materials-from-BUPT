
/**
 * @fileoverview Common utility functions to use with common and custom code.
 */
var utils = (function() {

  /**
   * @param {Element} element The element to check.
   * @param {!function(Element)} matcher The matcher function that is invoked
   *     with the element being traversed.
   * @return {Element} Returns the first element that matches the tag name
   *     by traversing up through the element's ancestors in the DOM tree.
   */
  function closestElement(element, matcher) {
    if (matcher(element)) {
      return element;
    }
    while (element && element.nodeType != 9 /* DOCUMENT */) {
      element = element.parentElement;
      if (element && matcher(element)) {
        return element;
      }
    }
    return null;
  }

  /**
   * Returns element by finding it within a group or via {@code getElementById}.
   * @param {string} targetID The ID attached to the element.
   * @param {number} opt_index Optional index to match when multiple instances
   *     of group used.
   * @return {Element} The element matching the ID.
   */
  function getElement(targetID, opt_index) {
    var targetElement;
    var index = opt_index || 0;
    var gwdId = new gwd.GwdId(targetID);
    var groupName = gwdId.getGroupName();
    if (groupName !== '') {
      var instances = document.querySelectorAll('[' +
          gwd.GwdId.GROUP_REFERENCE_ATTR + ' = ' + groupName + ']');
      if (instances && instances.length > index - 1) {
        var instance = instances[index];
        targetElement = gwdId.getElementInInstance(document, instance);
      }
    } else {
      var validId = targetID.split(' ').splice(-1)[0];
      targetElement = gwd.actions.events.getElementById(validId);
    }

    if (! targetElement) {
      throw new Error(targetID + ' ' + index + ' not found.');
    }

    return targetElement;
  }

  /**
   * Show or hide an element through opacity and visibility.
   * @param {Element} el Element
   * @param {boolean} state Visibility of element.
   */
  /**
   * Show or hide an element through opacity and visibility.
   * @param {Element} el Element
   * @param {boolean} state Visibility of element.
   */
  function showElement(el, state) {
    if (!el) return;
    if (state) {
      el.style.opacity = 1;
      el.style.visibility = 'visible';
    } else {
      el.style.opacity = 0;
      el.style.visibility = 'hidden';
    }
  }

  /**
   * Verifies if a string is really empty.
   * @param {string} str String to verify.
   * @return {boolean}
   */
  function isEmptyString(str) {
    if (!str) {
      return true;
    }
    str = str.trim();
    return !str || !str.length;
  }

  /**
   * Type convert string to boolean.
   * @param {string} val Value to convert to boolean.
   * @return {boolean}
   */
  function toBoolean(val) {
    return val.toLowerCase() == 'true';
  }

  /**
   * Determines whether two string values both exist and are unique.
   * @param {string} value1
   * @param {string} value2
   * @return {boolean}
   */
  function stringValuesAreUnique(value1, value2) {
    var valuesNotEqual = value1 != value2;
    var valuesBothEmpty = isEmptyString(value1) && isEmptyString(value2);
    return valuesNotEqual && ! valuesBothEmpty;
  }

  /**
   * Safe console warn.
   */
  function warn() {
    if (isGWDPreviewPage()) {
      if (console && console.warn) {
        for (var i = 0, length = arguments.length; i < length; i++) {
          console.warn(arguments[i]);
        }
      }
    }
  }

  /**
   * Safe console logger.
   */
  function log() {
    if (isGWDPreviewPage()) {
      if (console && console.log) {
        for (var i = 0, length = arguments.length; i < length; i++) {
          console.log(arguments[i]);
        }
      }
    }
  }

  /**
   * Determine whether ad exists within dev mode preview page.
   * @return {boolean}
   */
  function isGWDPreviewPage() {
    if (window.location.href.indexOf('gwd-preview') != -1 ||
        window.location.href.indexOf('gwd_preview') != -1) {
      return true;
    }
    return false;
  }


  return {
    closestElement: closestElement,
    showElement: showElement,
    getElement: getElement,
    isEmptyString: isEmptyString,
    toBoolean: toBoolean,
    stringValuesAreUnique: stringValuesAreUnique,
    log: log,
    warn: warn,
    isGWDPreviewPage: isGWDPreviewPage
  };
})();
