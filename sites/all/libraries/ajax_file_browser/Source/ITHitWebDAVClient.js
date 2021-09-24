
// Declare ITHit core.
if ('undefined' === typeof ITHit) {
	
	(function () {
		
		this.ITHit = {
			
			_oComponents: {},
			_oNamespace: {},
			
			// Define new modules.
			Define: function (sComponentName) {
				this._oComponents[sComponentName] = true;
			},
			
			// Check whether module has already been defined.
			Defined: function (sComponentName) {
				return !!this._oComponents[sComponentName];
			},
			
			// Add new modules.
			Add: function (sLable, mValue) {
				
				var aLable  = sLable.split('.');
				var oObj    = this;
				var iLength = aLable.length;
				
				for (var i = 0; i < iLength; i++) {
					
					if ('undefined' === typeof oObj[aLable[i]]) {
						if (i < (iLength - 1)) {
							oObj[aLable[i]] = {};
						} else {
							oObj[aLable[i]] = mValue;
						}
					} else {
						if (!(oObj[aLable[i]] instanceof Object)) {
							return;
						}
					}
					
					oObj = oObj[aLable[i]];
				}
			},
			
			// Temporary object.
			Temp: {}
		};
	})();
	
}

// Declare ITHit Config.
ITHit.Config = {
	Global: window,
	ShowOriginalException: true,
	// Whether UNIX timestamp needs to be added to URI for XMLHttpRequest for prevanting caching.
	PreventCaching: false
};

/*
* Method for getting namespace.
* @class
*
* @param {String/Array mNamespace} Namespace for getting/creating
* @param {Boolean} bCreate If whether namespace need to be created
* @param {Object} oContext Context from witch will be created namespace
* @returns Namespace object if exists or "undefined" otherwise
*/
ITHit.Add('GetNamespace', 
	function(mNamespace, bCreate, oContext) {
		
		var utilsNs = ITHit.Utils;
		
		// Namespace type checking
		if ( !utilsNs.IsString(mNamespace)
			&& !utilsNs.IsArray(mNamespace)
		) {
			throw new ITHit.Exception('ITHit.GetNamespace() expected string as first parameter of method.');
		}
			
		var aNamespace = utilsNs.IsArray(mNamespace) ? mNamespace : mNamespace.split('.');
		
		// Context
		var oObj = oContext || ITHit.Config.Global;
		
		// Creating or selecting namespace
		for (var i = 0, sPart = ''; oObj && (sPart = aNamespace[i]); i++) {
			
			if (sPart in oObj) {
				oObj = oObj[sPart];
			} else {
				if (bCreate) {
					oObj[sPart] = {};
					oObj = oObj[sPart];
				} else {
					oObj = undefined;
				}
			}
		}
		
		// Return selected namespace
		return oObj;
	}
);

/*
*
* @method ITHit.Namespace
* 
* @param {String} sNamespace 
* @param {Object} oOntext 
* @returns Namespace object if exists or "undefined" otherwise
*/
ITHit.Add('Namespace',
	function (sNamespace, oContext) {
		return ITHit.GetNamespace(sNamespace, false, oContext);
	}
);

/*
* 
* @method ITHit.Declare
* 
* @param {String} sNamespace 
* @param {Object} oOntext 
* @returns Namespace object if exists or "undefined" otherwise
*/
ITHit.Add('Declare',
	function (sNamespace, oContext) {
		return ITHit.GetNamespace(sNamespace, true, oContext);
	}
);

ITHit.Add('DetectOS',
	function () {
	    var _plat = navigator.platform,
		    detectOS = {
		        Windows: (-1 != _plat.indexOf('Win')),
		        MacOS: (-1 != _plat.indexOf('Mac')),
		        IOS: (/iPad|iPhone|iPod/.test(_plat)),
		        Linux: (-1 != _plat.indexOf('Linux')),
		        UNIX: (-1 != _plat.indexOf('X11')),
		        OS: null
		    };

	    if (detectOS.Windows) {
	        detectOS.OS = 'Windows';
	    } else if (detectOS.Linux) {
	        detectOS.OS = 'Linux';
	    } else if (detectOS.MacOS) {
	        detectOS.OS = 'MacOS';
	    } else if (detectOS.UNIX) {
	        detectOS.OS = 'UNIX';
	    } else if (detectOS.IOS) {
	        detectOS.OS = 'IOS';
	    }

	    return detectOS;
	}()
);

ITHit.Add('DetectBrowser',
	function () {
	    var _nav = navigator.userAgent,
			detectBrowser = {
			    IE: false,
			    FF: false,
			    Chrome: false,
			    Safari: false,
			    Opera: false,
			    Browser: null,
			    Mac: false
			},
			browsers = {
			    /*IE 10 and earlier*/
			    IE: {
			        Search: 'MSIE',
			        Browser: 'IE'
			    },
			    IE11: {
			        Search: 'Trident/7',
			        Version: 'rv',
			        Browser: 'IE'
			    },
				Edge: {
					Search: 'Edge',
					Browser: 'Edge'
				},
			    FF: {
			        Search: ['Firefox', 'FxiOS'],
			        Browser: 'FF'
			    },
			    Chrome: {
			        Search: 'Chrome',
			        Browser: 'Chrome'
			    },
			    Safari: {
			        Search: 'Safari',
			        Version: 'Version',
			        Browser: 'Safari',
			        Mac: 'Macintosh',
			        iPad: 'iPad',
					iPhone: 'iPhone'
			    },
			    Opera: {
			        Search: 'Opera',
			        Browser: 'Opera'
			    }
			};
	 
	    for (var check in browsers) {
	        var pos = -1;    	        
	        if (Array.isArray(browsers[check].Search)) {
	            for (var i = 0; i < browsers[check].Search.length; i++) {
	                pos = _nav.indexOf(browsers[check].Search[i]);
	                if (-1 != pos)
	                    break;
	            }
	        } else {
	            pos = _nav.indexOf(browsers[check].Search);
	        }
	        
	        if (-1 != pos) {
	            detectBrowser.Browser = browsers[check].Browser;
	            detectBrowser.Mac = navigator.platform.indexOf('Mac') == 0; //(browsers[check].Mac && _nav.indexOf(browsers[check].Mac) != -1);
	            detectBrowser.iPad = (browsers[check].iPad && _nav.indexOf(browsers[check].iPad) != -1);
				detectBrowser.iPhone = (browsers[check].iPhone && _nav.indexOf(browsers[check].iPhone) != -1);

	            var search = Array.isArray(browsers[check].Search) ? browsers[check].Search[0] : browsers[check].Search;
	            var versionSearch = browsers[check].Version || search,
					index = _nav.indexOf(versionSearch);

	            if (-1 == index) {
	                detectBrowser[browsers[check].Browser] = true;
	                break;
	            }

	            detectBrowser[browsers[check].Browser] = parseFloat(_nav.substring(index + versionSearch.length + 1));

	            break;
	        }
	    }
	    return detectBrowser;
	}()
);

ITHit.Add('DetectDevice',
	function() {
		var sUserAgent = navigator.userAgent;
		var resultDevices = {};
		var devices = {
			Android: {
				Search: 'Android'
			},
			BlackBerry: {
				Search: 'BlackBerry'
			},
			iOS: {
				Search: 'iPhone|iPad|iPod'
			},
			Opera: {
				Search: 'Opera Mini'
			},
			Windows: {
				Search: 'IEMobile'
			},
			Mobile: {
			}
		};

		for (var name in devices) {
			var oParams = devices[name];
			if (!oParams.Search) {
				continue;
			}

			// Detect device
			var oRegExp = new RegExp(oParams.Search, 'i');
			resultDevices[name] = oRegExp.test(sUserAgent);

			// Set any
			if (!resultDevices.Mobile && resultDevices[name]) {
				resultDevices.Mobile = true;
			}
		}

		return resultDevices;
	}()
);

ITHit.Add('HttpRequest',
	function(sHref, sMethod, oHeaders, sBody, sUser, sPass) {
		
		if (!ITHit.Utils.IsString(sHref)) {
			throw new ITHit.Exception('Expexted string href in ITHit.HttpRequest. Passed: "'+ sHref +'"', 'sHref');
		}
		
		if (!ITHit.Utils.IsObjectStrict(oHeaders) && !ITHit.Utils.IsNull(oHeaders) && !ITHit.Utils.IsUndefined(oHeaders)) {
			throw new ITHit.Exception('Expexted headers list as object in ITHit.HttpRequest.', 'oHeaders');
		}
		
		this.Href     = sHref;
		this.Method   = sMethod;
		this.Headers  = oHeaders;
		this.Body     = sBody;
		this.User     = sUser || null;
		this.Password = sPass || null;
	}
);

ITHit.Add('HttpResponse',
	function() {
		
		var HttpResponse = function(sHref, iStatus, sStatusDescription, oHeaders) {
			
			if (!ITHit.Utils.IsString(sHref)) {
				throw new ITHit.Exception('Expexted string href in ITHit.HttpResponse. Passed: "'+ sHref +'"', 'sHref');
			}
			
			if (!ITHit.Utils.IsInteger(iStatus)) {
				throw new ITHit.Exception('Expexted integer status in ITHit.HttpResponse.', 'iStatus');
			}
			
			if (!ITHit.Utils.IsString(sStatusDescription)) {
				throw new ITHit.Exception('Expected string status description in ITHit.HttpResponse.', 'sStatusDescription');
			}
			
			if (oHeaders && !ITHit.Utils.IsObjectStrict(oHeaders)) {
				throw new ITHit.Exception('Expected object headers in ITHit.HttpResponse.', 'oHeaders');
			}
			else if (!oHeaders) {
				oHeaders = {};
			}
			
			this.Href              = sHref;
			this.Status            = iStatus;
			this.StatusDescription = sStatusDescription;
			this.Headers           = oHeaders;
			this.BodyXml           = null;
			this.BodyText          = '';
		}
		
		HttpResponse.prototype._SetBody = function(oBodyXml, sBodyText) {
			this.BodyXml  = oBodyXml  || null;
			this.BodyText = sBodyText || '';
		}
		
		HttpResponse.prototype.SetBodyText = function(sBody) {
			this.BodyXml  = null;
			this.BodyText = sBody;
		}
		
		HttpResponse.prototype.SetBodyXml = function(oBody) {
			this.BodyXml  = oBody;
			this.BodyText = '';
		}
		
		HttpResponse.prototype.ParseXml = function(sXml) {
			
			if (!ITHit.Utils.IsString(sXml)) {
				throw new ITHit.Exception('Expected XML string in ITHit.HttpResponse.ParseXml', 'sXml');
			}
			
			var oXml = new ITHit.XMLDoc();
			oXml.load(sXml);
			
			this.BodyXml  = oXml._get();
			this.BodyText = sXml;
		}
		
		HttpResponse.prototype.GetResponseHeader = function(sHeader, bToLowerCase) {
			
			if (!bToLowerCase) {
				return this.Headers[sHeader];
			}
			else {
				var sHeader = String(sHeader).toLowerCase();
				
				for (var sHeaderName in this.Headers) {
					if (sHeader === String(sHeaderName).toLowerCase()) {
						return this.Headers[sHeaderName];
					}
				}
				
				return undefined;
			}
		}
		
		return HttpResponse;
	}()
);

ITHit.Add('XMLRequest',
	(function() {

	    var XMLObjectVersion;

	    /*
		* Get XMLHttpRequest method.
		* @method XMLRequest
		*
		* @throws {Object} Exception Whether object cannot be created.
		*/
	    var GetXMLObject = function () {
	        // Get XMLHttpRequest object in IE.
	        if (ITHit.DetectBrowser.IE && ITHit.DetectBrowser.IE < 10 && window.ActiveXObject) {

	            if (XMLObjectVersion) {
	                return new ActiveXObject(XMLObjectVersion)
	            }
	            else {
	                var aVers = ["MSXML2.XmlHttp.6.0", "MSXML2.XmlHttp.3.0"];
	                for (var i = 0; i < aVers.length; i++) {
	                    try {
	                        var oXmlObj = new ActiveXObject(aVers[i]);
	                        XMLObjectVersion = aVers[i];
	                        return oXmlObj;
	                    }
	                    catch (e) {
	                    }
	                }
	            }

	            // Get XMLHttpRequest object in W3C compatible browsers.
	        } else if ('undefined' != typeof XMLHttpRequest) {
	            return new XMLHttpRequest();
	        }

	        // Whether XMLHttpRequest object has not been created.
	        throw new ITHit.Exception('XMLHttpRequest (AJAX) not supported');
	    }

	    var parseResponseHeaders = function (sHeaders) {

	        var oHeaders = {};

	        if (!sHeaders) {
	            return oHeaders;
	        }

	        var aHeaders = sHeaders.split('\n');
	        for (var i = 0; i < aHeaders.length; i++) {

	            if (!ITHit.Trim(aHeaders[i])) {
	                continue;
	            }

	            var aParts = aHeaders[i].split(':');
	            var sHeaderName = aParts.shift();

	            oHeaders[sHeaderName] = ITHit.Trim(aParts.join(':'));
	        }

	        return oHeaders;
	    }

        var XMLRequest = function(oHttpRequest, bAsync) {

            // Set true, if need async request and register callback through XMLRequest.OnData() method
            this.bAsync = bAsync === true;

            this.IsAborted = false;
            // Listeners for async requests
			this.OnData = null;
			this.OnError = null;
			this.OnProgress = null;
            this.OnUploadProgress = null;

            this.oHttpRequest = oHttpRequest;
            this.oError = null;

            // Check whether url is empty.
            if (!oHttpRequest.Href) {
                throw new ITHit.Exception('Server url had not been set.');
            }

            if (ITHit.Logger && ITHit.LogLevel) {
                ITHit.Logger.WriteMessage('[' + oHttpRequest.Href + ']');
            }

            this.oRequest = GetXMLObject();

            var sHref   = String(oHttpRequest.Href);
            var sMethod = oHttpRequest.Method || 'GET';

            try {
				if (oHttpRequest.User){
					this.oRequest.open(sMethod, ITHit.DecodeHost(sHref), this.bAsync, oHttpRequest.User, oHttpRequest.Password);
				}else{
					// FIX bug with passed null:null as user:pass on digest auth on Chrome
					this.oRequest.open(sMethod, ITHit.DecodeHost(sHref), this.bAsync);
				}

                if (ITHit.DetectBrowser.IE && ITHit.DetectBrowser.IE >= 10) {
                    try {
                        this.oRequest.responseType = 'msxml-document';
                    } catch (e) {
                    }
                }
                // Initialization failed.
            } catch(e) {

                // Get host of requested page.
                var aDestHost = sHref.match(/(?:\/\/)[^\/]+/);

                // Check whether host is found.
                if (aDestHost) {
                    var sDestHost = aDestHost[0].substr(2);

                    // Check whether root host and destination host is not the same.
                    if (XMLRequest.Host != sDestHost) {
                        // Cross-domain request, throw an exception.
                        throw new ITHit.Exception(ITHit.Phrases.CrossDomainRequestAttempt.Paste(window.location, sHref, String(sMethod)), e);

                        // Another reason.
                    } else {
                        throw e;
                    }
                }
            }

            // Set headers.
            for (var sHeader in oHttpRequest.Headers) {
                this.oRequest.setRequestHeader(sHeader, oHttpRequest.Headers[sHeader]);
            }

			if (this.bAsync) {
				try {
					this.oRequest.withCredentials = true;
				} catch(e) {}
			}

            if (this.bAsync) {
                var self = this;
                this.oRequest.onreadystatechange = function() {
                    if (self.oRequest.readyState != 4) {
                        return;
                    }

                    var oResponse = self.GetResponse();
					if (typeof self.OnData === 'function') {
						self.OnData.call(self, oResponse);
					}
                };
				if ('onprogress' in this.oRequest) {
					this.oRequest.onprogress = function(oEvent) {
						if (typeof self.OnProgress === 'function') {
							self.OnProgress.call(self, oEvent);
						}
					};
				}
                if (this.oRequest.upload && 'onprogress' in this.oRequest) {
                    this.oRequest.upload.onprogress = function(oEvent) {
                        if (typeof self.OnUploadProgress === 'function') {
                            self.OnUploadProgress.call(self, oEvent);
                        }
                    };
                }
            }
        }

        XMLRequest.prototype.Send = function() {
            // Get body as string.
            var sBody = this.oHttpRequest.Body;
            sBody = sBody || (ITHit.Utils.IsUndefined(sBody) || ITHit.Utils.IsNull(sBody) || ITHit.Utils.IsBoolean(sBody) ? '' : sBody);

            if (sBody === ''){
                sBody = null;
            }

            // Try to send request.
            try {
                this.oRequest.send(sBody);
            } catch (e) {
                this.oError = e;

				if (typeof this.OnError === 'function') {
					this.OnError.call(this, e);
				}
            }
        }

		XMLRequest.prototype.Abort = function() {
			if (this.oRequest) {
				try {
                    this.IsAborted = true;
					this.oRequest.abort();
				} catch (e) {
					this.oError = e;

					if (typeof this.OnError === 'function') {
						this.OnError.call(this, e);
					}
				}
			}
		}

        XMLRequest.prototype.GetResponse = function() {
            var oHttpRequest = this.oHttpRequest;
            var oRequest = this.oRequest;
            var sHref   = String(oHttpRequest.Href);

            if (this.bAsync && oRequest.readyState != 4) {
                throw new ITHit.Exception('Request sended as asynchronous, please register callback through XMLRequest.OnData() method for get responce object.');
            }

            // Throw an exception whether module is not loaded. But ignore error if we are uploading JS file with PROPFIND method.
            if ((404 == oRequest.status) && (-1 != sHref.indexOf('.js') && (oHttpRequest.Method !== "PROPFIND"))) {
                ITHit.debug.loadTrace.failed(ITHit.debug.loadTrace.FAILED_LOAD);
                throw new ITHit.Exception('Failed to load script ("' + sHref + '"). Request returned status: '+ oRequest.status + (oRequest.statusText ? ' ('+ oRequest.statusText +')' :'') +'.', this.oError || undefined);
            }

            // Fix request status whether it is necessary.
            var oStatus   = this.FixResponseStatus(oRequest.status, oRequest.statusText);
            var oResponse = new ITHit.HttpResponse(sHref, oStatus.Status, oStatus.StatusDescription, parseResponseHeaders(oRequest.getAllResponseHeaders()));
            oResponse._SetBody(oRequest.responseXML, oRequest.responseText);

            return oResponse;
        }

        /*
         * Fix response status. Whether it is necessary and can be done.
         * @function {Object} ITHit.XMLRequest.fixResponseStatus
         *
         * @param {Integer} iStatus Response status.
         * @param {String} sStatusText Status text.
         */
        XMLRequest.prototype.FixResponseStatus = function(iStatus, sStatusText) {

            var oStatus = {
                Status: iStatus,
                StatusDescription: sStatusText
            };

            // Fix for IE7 browser for PUT method 204 status code.
            if (1223 == iStatus) {
                oStatus.Status            = 204;
                oStatus.StatusDescription = 'No Content';
            }

            return oStatus;
        }

        XMLRequest.Host = window.location.host;
		

		
		return XMLRequest;
	})()
);

ITHit.Add('Utils',
	{
		// Check variable type.
		
		IsString: function(mValue) {
			return ( ('string' == typeof mValue) || (mValue instanceof String) );
		},
		
		IsNumber: function(mValue) {
			return ('number' == typeof mValue);
		},
		
		IsBoolean: function(mValue) {
			return ( ('boolean' == typeof mValue) || (mValue instanceof Boolean) );
		},
		
		IsInteger: function(mValue) {
			return this.IsNumber(mValue) && (-1 == String(mValue).indexOf('.'));
		},
		
		IsArray: function(mValue) {
			return (mValue instanceof Array || ('array' == typeof mValue));
		},
		
		IsFunction: function(mValue) {
			return (mValue instanceof Function);
		},
		
		IsObject: function(mValue) {
			return ('object' == typeof mValue);
		},
		
		IsDate: function(mValue) {
			return (mValue instanceof Date)
		},
		
		IsRegExp: function(mValue) {
			return (mValue instanceof RegExp);
		},
		
		IsObjectStrict: function(mValue) {
			return this.IsObject(mValue) && !this.IsArray(mValue) && !this.IsString(mValue) && !this.IsNull(mValue) && !this.IsNumber(mValue) && !this.IsDate(mValue) && !this.IsRegExp(mValue) && !this.IsBoolean(mValue) && !this.IsFunction(mValue) && !this.IsNull(mValue);
		},
		
		IsUndefined: function(mValue) {
			return (undefined === mValue);
		},
		
		IsNull: function(mValue) {
			return (null === mValue);
		},
		
		IsDOMObject: function(mValue) {
			return mValue && this.IsObject(mValue) && !this.IsUndefined(mValue.nodeType);
		},

		HtmlEscape: function(text) {
			return String(text)
				.replace(/&/g, '&amp;')
				.replace(/"/g, '&quot;')
				.replace(/'/g, '&#39;')
				.replace(/</g, '&lt;')
				.replace(/>/g, '&gt;');
		},

		IndexOf: function(array, item, isSorted) {
			var i = 0, length = array && array.length;
			if (typeof isSorted == 'number') {
				i = isSorted < 0 ? Math.max(0, length + isSorted) : isSorted;
			}
			for (; i < length; i++) if (array[i] === item) return i;
			return -1;
		},
		
		Contains: function(array, item) {
			return array
				&& item
				&& this.IsArray(array)
				&& (this.IndexOf(array, item) >= 0);
		},
        FindBy: function(array, fCallBack, thisArg) {
            if (array.find) return array.find(fCallBack, thisArg);
            for (var i = 0; i < array.length; i++) {
                var oElement = array[i];
                if (fCallBack(oElement, i, array)) {
                    return oElement;
                }
            }

            return undefined;
        },
        FilterBy: function(array, fCallBack, thisArg) {
            var aFiltered = [];
            if (array.filter) return array.filter(fCallBack, thisArg);
            for (var i = 0; i < array.length; i++) {
                var oElement = array[i];
                if (fCallBack(oElement, i, array)) {
                    aFiltered.push(oElement);
                }
            }

            return aFiltered;
        },

        NoOp: function(){},
		/*
		 * Create DOM Element.
		 * @function CreateDOMElement
		 * 
		 * @paramset Syntax 1
		 * @param {string} elem  Node name.
		 * @param {String} props Node propertyes.
		 * @paramset Syntax 2
		 * @param {Object} elem Node object. Node name must be specified in nodeName property.
		 */
		CreateDOMElement: function(elem, props) {
	
			var utilsNs = ITHit.Utils;
			
			if (utilsNs.IsObject(elem)) {
				if (!elem.nodeName) {
					throw new ITHit.Exception('nodeName property does not specified.');
				}
				props = elem;
				elem = elem.nodeName;
				delete props.nodeName;
			}
			
			// Create new element.
			var newElem = document.createElement(elem);
			
			// Assign properties.
			if (props && utilsNs.IsObject(props)) {
				for (var propName in props) {
					if (!props.hasOwnProperty(propName)) 
						continue;
					
					switch (propName) {
					
						// Replace property class with className.
						case 'class':
							if (props[propName]) {
								newElem.className = props[propName];
							}
							break;
							
						// Style
						case 'style':
							var stylesList = props[propName];
							for (var style in stylesList) {
								if (!stylesList.hasOwnProperty(style)) 
									continue;
								
								newElem.style[style] = stylesList[style];
							}
							break;
							
						// Append child nodes.
						case 'childNodes':
							for (var i = 0, l = props[propName].length; i < l; i++) {
								var child = props[propName][i];
								
								// Create text node and continue.
								if (utilsNs.IsString(child) || utilsNs.IsNumber(child) || utilsNs.IsBoolean(child)) {
									child = document.createTextNode(child);
									
								// Continue loop whether value is not set.
								}
								else 
									if (!child) {
										continue;
									}
								
								if (!utilsNs.IsDOMObject(child)) {
									child = ITHit.Utils.CreateDOMElement(child);
								}
								
								// Add child node.
								newElem.appendChild(child);
							}
							break;
							
						default:
							newElem[propName] = props[propName];
					}
				}	
			}
			
			return newElem;
		},
		
		GetComputedStyle: function(node) {
			
			// First call binding.
			ITHit.Utils.GetComputedStyle = ITHit.Components.dojo.getComputedStyle;
			
			return ITHit.Utils.GetComputedStyle(node);
		},
		
		MakeScopeClosure: function(scope, method, params) {
			if (this.IsUndefined(params)) {
				return this._GetClosureFunction(scope, method);
			} else {
				if (!this.IsArray(params)) {
					params = [params];
				}
				return this._GetClosureParamsFunction(scope, method, params);
			} 
		},
		
		_GetClosureParamsFunction: function(scope, method, params) {
			return function() {
					
					var args = [];
					for (var i = 0, l = params.length; i < l; i++) {
						args.push(params[i]);
					}
					
					if (arguments.length) {
						for (var i = 0, l = arguments.length; i < l; i++) {
							args.push(arguments[i]);
						}
					}
					if(ITHit.Utils.IsFunction(method)){
						method.apply(scope, args);
					} else {
						scope[method].apply(scope, args);
					}
			};
		},
		
		_GetClosureFunction: function(scope, method) {
			return function() {
				if(ITHit.Utils.IsFunction(method)){
					return method.apply(scope, arguments);
				};
				return scope[method].apply(scope, arguments);
			};
		}
	}
);

/*
 * Removes initial and final space characters.
 * @function {static String} ITHit.Trim
 * 
 * @param {Object} sText Text to trim.
 * @param {Object} sType Trim type.
 * @param {Object} bHardCheck Whether first parameter must be string type. Default is false.
 * 
 * @throw {ITHit.Exception} If not string passed as first parameter and bHardCheck is set to true.
 */
ITHit.Add('Trim',
	function (sText, sType, bHardCheck) {
		
		if ( ('string' != typeof sText) && !(sText instanceof String) ) {
			if (!bHardCheck) {
				return sText;
			} else {
				throw new ITHit.Exception('ITHit.Trim() expected string as first prameter.');
			}
		}
		
		switch (sType) {
		
			case ITHit.Trim.Left:
				return sText.replace(/^\s+/, '');
				break;
				
			case ITHit.Trim.Right:
				return sText.replace(/\s+$/, '');
				break;
				
			default:
				return sText.replace(/(?:^\s+|\s+$)/g, '');
		}
	}
);

/*
 * Trim only initial space chars.
 * @property {String} ITHit.Trim.Left
 */
ITHit.Add('Trim.Left',  'Left');

/*
 * Trim only final space chars.
 * @property {String} ITHit.Trim.Right
 */
ITHit.Add('Trim.Right', 'Right');

/*
 * Trim initial and final space chars.
 * @property {String} ITHit.Trim.Both
 */
ITHit.Add('Trim.Both',  'Both');

/**
 * Base class for exceptions.
 * @class ITHit.Exception
 */
ITHit.Add('Exception',
	(function () {
		
		/*
		 * Create instance of Exception class.
		 * @constructor Exception
		 * 
		 * @param {String} sMessage Exception message.
		 * @param {optional Object} oInnerException Original exception.
		 */
		var Exception = function (sMessage, oInnerException) {
			
			/**
			 * Exception message.
			 * @property {String} ITHit.Exception.Message
			 */
			this.Message = sMessage;
			
			/**
			 * Original exception that caused this exception.
			 * @property {ITHit.Exception}  ITHit.Exception.InnerException
			 */
			this.InnerException = oInnerException;
			
			// Whether exception must be logged.
			if (ITHit.Logger.GetCount(ITHit.LogLevel.Error)) {
				
				var sException =
					'Exception: '+ this.Name +'\n'
					+ 'Message: '+ this.Message +'\n';
				
				if (oInnerException) {
					sException += ((!oInnerException instanceof Error) ? 'Inner exception: ' : '')
						+ this.GetExceptionsStack(oInnerException);
					
				}
				
				// Log exception.
				ITHit.Logger.WriteMessage(sException, ITHit.LogLevel.Error);
			}
		}
		
		/*
		 * Exception title.
		 * @property {private String} ITHit.Exception.Name
		 */
		Exception.prototype.Name = 'Exception';
		
		/*
		 * Returns oririginal exceptions.
		 * @function {private String} ITHit.Exception.GetExceptionsStack
		 * 
		 * @param {Object} oException 
		 * @param {Integer} iLevel 
		 * 
		 * @returns Stack of original exceptions.
		 */
		Exception.prototype.GetExceptionsStack = function (oException, iLevel) {
			
			if ('undefined' === typeof oException) {
				var oException = this;
			}
			
			var iLevel = iLevel ? iLevel : 0;
			var sStr = '';
			var sSingleMargin = '      ';
			var sMargin = '';
			for (var i = 0; i < iLevel; i++) {
				sMargin += sSingleMargin;
			}
			
			if (oException instanceof ITHit.Exception) {
				sStr += sMargin + (oException.Message ? oException.Message : oException) + '\n';
			} else {
				if (ITHit.Config.ShowOriginalException) {
					sStr += '\nOriginal exception:\n';
					if ( ('string' != typeof oException) && !(oException instanceof String) ) {
						for (var sProp in oException) {
							sStr += '\t' + sProp + ': "' + ITHit.Trim(oException[sProp]) + '"\n';
						}
					} else {
						sStr += '\t' + oException +'\n';
					}
				}
			}
			
			return sStr;
		}
		
		/*
		 * Convert object to string.
		 * @function {String} ITHit.Exception.toString
		 * 
		 * @returns Stack of original exceptions.
		 */
		Exception.prototype.toString = function () {
			return this.GetExceptionsStack();
		}
		
		return Exception;
	})()
);

/*
 * Method for emulating classical inharitance for javascript.
 * @function {static} ITHit.Extend
 * 
 * @param {Object} subClass Class to extend.
 * @param {Object} baseClass Base class.
 */
ITHit.Add('Extend',
	function (subClass, baseClass){
		
		function inheritance(){};
		
		inheritance.prototype = baseClass.prototype;
		
		// set prototype to new instance of baseClass
		// _without_ the constructor
		subClass.prototype = new inheritance();
		subClass.prototype.constructor = subClass;
		subClass.baseConstructor = baseClass;
		
		// enable multiple inheritance
		if (baseClass.base) {
			baseClass.prototype.base = baseClass.base;
		}
		
		subClass.base = baseClass.prototype;
	}
);

ITHit.Add('Events',
	function() {

		var Events = function() {
			this._Listeners      = this._NewObject();
			this._DispatchEvents = {};
			this._DelayedDelete  = {};
		}

		Events.prototype._NewObject = function() {

			var obj = {};
			for (var prop in obj) {
				delete obj[prop];
			}

			return obj;
		}

		Events.prototype.AddListener = function(oObject, sEventName, mHandler, mHandlerScope) {

			var sInstanceName = oObject.__instanceName;

			var oHandler;
			var oNsHandler = ITHit.EventHandler;

			if (!(mHandler instanceof ITHit.EventHandler)) {
				oHandler = new ITHit.EventHandler(mHandlerScope || null, mHandler);
			}
			else {
				oHandler = mHandler;
			}

			var oListeners = this._Listeners[sInstanceName] || (this._Listeners[sInstanceName] = this._NewObject());
			var oEventHandlers = oListeners[sEventName] || (oListeners[sEventName] = []);

			var bFounded = false;
			for (var i = 0, l = oEventHandlers.length; i < l; i++) {
				if (oEventHandlers[i].IsEqual(oHandler)) {
					bFounded = true;
					break;
				}
			}

			if (!bFounded) {
				oEventHandlers.push(oHandler);
			}
		}

		Events.prototype.DispatchEvent = function(oObject, sEventName, mData) {

			var sInstanceName = oObject.__instanceName;

			if (!this._Listeners[sInstanceName] || !this._Listeners[sInstanceName][sEventName] || !this._Listeners[sInstanceName][sEventName].length) {
				return undefined;
			}

			var oNsHandler = ITHit.EventHandler;
			var bRet;
			var oHandlers  = [];
			for (var i = 0, l = this._Listeners[sInstanceName][sEventName].length; i < l; i++) {
				oHandlers.push(this._Listeners[sInstanceName][sEventName][i]);
			}

			this._DispatchEvents[sInstanceName] = (this._DispatchEvents[sInstanceName] || 0) + 1;
			this._DispatchEvents[sInstanceName+':'+sEventName] = (this._DispatchEvents[sInstanceName+':'+sEventName] || 0) + 1;

			for (var i = 0; i < oHandlers.length; i++) {

				var bForRet;

				if (oHandlers[i] instanceof oNsHandler) {
					try {
						bForRet = oHandlers[i].CallHandler(oObject, sEventName, mData);
					} catch(e) {
						throw e;
					}
				}
				if (oHandlers[i] instanceof Function) {
					try {
						bForRet = oHandlers[i](oObject, sEventName, mData);
					} catch(e) {
						throw e;
					}
				}

				if (!ITHit.Utils.IsUndefined(bForRet)) {
					bRet = bForRet;
				}
			}

			this._DispatchEvents[sInstanceName]--;
			this._DispatchEvents[sInstanceName+':'+sEventName]--;

			this._CheckDelayedDelete(oObject, sEventName);

			return bRet;
		}

		Events.prototype.RemoveListener = function(oObject, sEventName, mHandler, mHandlerScope) {

			var sInstanceName = oObject.__instanceName;

			mHandlerScope = mHandlerScope || null;

			if (!this._Listeners[sInstanceName] || !this._Listeners[sInstanceName][sEventName] || !this._Listeners[sInstanceName][sEventName].length) {
				return true;
			}

			var aHandlers = this._Listeners[sInstanceName][sEventName];
			for (var i = 0, l = aHandlers.length; i < l; i++) {
				if (aHandlers[i].IsEqual(mHandlerScope, mHandler)) {
					this._Listeners[sInstanceName][sEventName].splice(i, 1);
					break;
				}
			}
		}

		Events.prototype.RemoveAllListeners = function(oObject, sEventName) {

			var sInstanceName = oObject.__instanceName;

			if (!ITHit.Utils.IsUndefined(sEventName)) {
				if (ITHit.Utils.IsUndefined(this._DispatchEvents[sInstanceName +':'+ sEventName])) {
					delete this._Listeners[sInstanceName][sEventName];
				} else {
					this._DelayedDelete[sInstanceName +':'+ sEventName] = true;
				}

			} else {
				if (ITHit.Utils.IsUndefined(this._DispatchEvents[sInstanceName])) {
					delete this._Listeners[sInstanceName];
				} else {
					this._DelayedDelete[sInstanceName] = true;
				}
			}

		}

		Events.prototype._CheckDelayedDelete = function(oObject, sEventName) {

			var sInstanceName = oObject.__instanceName;

			if (!this._DispatchEvents[sInstanceName+':'+sEventName]) {
				delete this._DispatchEvents[sInstanceName+':'+sEventName];
				if (!ITHit.Utils.IsUndefined(this._DelayedDelete[sInstanceName +':'+ sEventName])) {
					this.RemoveAllListeners(oObject, sEventName);
				}
			}
			if (!this._DispatchEvents[sInstanceName]) {
				delete this._DispatchEvents[sInstanceName];
				if (!ITHit.Utils.IsUndefined(this._DelayedDelete[sInstanceName])) {
					this.RemoveAllListeners(oObject);
				}
			}
		}

		Events.prototype.ListenersLength = function(oObject, sEventName) {

			var sInstanceName = oObject.__instanceName;

			if (!this._Listeners[sInstanceName] || !this._Listeners[sInstanceName][sEventName]) {
				return 0;
			}

			return this._Listeners[sInstanceName][sEventName].length;
		}

		Events.prototype.Fix = function(e) {

			// Get event.
			e = e || window.event;

			// Get target element.
			if (!e.target && e.srcElement) {
				e.target = e.srcElement;
			}

			// Calculate pageX, pageY if not defined.
			if ((null == e.pageX) && (null != e.clientX)) {
				var html = document.documentElement,
					body = document.body;
				e.pageX = e.clientX + (html && html.scrollLeft || body && body.scrollLeft || 0) - (html.clientLeft || 0);
				e.pageY = e.clientY + (html && html.scrollTop || body && body.scrollTop || 0) - (html.clientTop || 0);
			}

			// Fix mouse button definition.
			if (!e.which && e.button) {
				e.which = e.button & 1 ? 1 : ( e.button & 2 ? 3 : ( e.button & 4 ? 2 : 0 ) );
			}

			return e;
		}

		Events.prototype.AttachEvent = function(elem, eventName, handler) {

			eventName = eventName.replace(/^on/, '');

			if (elem.addEventListener) {
				elem.addEventListener(eventName, handler, false);
			} else if(elem.attachEvent) {
				elem.attachEvent('on'+ eventName, handler);
			} else {
				elem['on'+ eventName] = handler;
			}
		}

		Events.prototype.DettachEvent = function(elem, eventName, handler) {

			eventName = eventName.replace(/^on/, '');

			if (elem.removeEventListener) {
				elem.removeEventListener(eventName, handler, false);
			} else if(elem.detachEvent) {
				elem.detachEvent('on'+ eventName, handler);
			} else {
				elem['on'+ eventName] = null;
			}
		}

		Events.prototype.Stop = function(e) {
			e = e || window.event;

			if (e.stopPropagation) {
				e.stopPropagation();
			}

			if (e.preventDefault) {
				e.preventDefault();
			} else {
				e.returnValue  = false;
			}

			e.cancelBubble = true;

			return false;
		}

		return new Events();

	}()
);

ITHit.Add('EventHandler',
	function() {
		var EventHandler = function(oScope, mMethod) {

			var oNsUtils = ITHit.Utils;

			if (!oNsUtils.IsObjectStrict(oScope) && !oNsUtils.IsNull(oScope)) {
				throw new ITHit.Exception('Event handler scope expected to be an object.');
			}

			if (!oNsUtils.IsFunction(mMethod) && (oScope && !oNsUtils.IsString(mMethod))) {
				throw new ITHit.Exception('Method handler expected to be a string or function.');
			}

			if (oScope) {
				this.Scope = oScope;
				this.Name = oScope.__instanceName;
			} else {
				this.Scope = window;
				this.Name = 'window';
			}

			this.Method = mMethod;
		}

		EventHandler.prototype.IsEqual = function(oScopeOrEventHandler, mMethod) {

			if (oScopeOrEventHandler instanceof ITHit.EventHandler) {
				return this.GetCredentials() === oScopeOrEventHandler.GetCredentials();
			}
			else {
				return ((oScopeOrEventHandler || null) === this.Scope) && (mMethod === this.Method);
			}
		}

		EventHandler.prototype.GetCredentials = function() {
			return this.Name + '::' + this.Method;
		}
		
		EventHandler.prototype.CallHandler = function(oScope, sEvent, aParams) {
				
			if ( !(aParams instanceof Array) ) {
				aParams = [aParams];
			}
			
			if (this.Scope) {
				
				if (this.Method instanceof Function) {
					return this.Method.apply(this.Scope || window, aParams.concat([oScope]));
				}
				else {
					try {
						return this.Scope[this.Method].apply(this.Scope, aParams.concat([oScope]));
					} catch(e) {
						throw new ITHit.Exception(e);
					}
				}
				
			}
			else {
				return this.Method.apply({}, aParams.concat([oScope]));
			}
		}
		
		return EventHandler;
	}()
);

ITHit.Add('HtmlEncode',
	function (sText) {
		return sText.replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/'/g, '&amp;').replace(/"/g, '&quot;');
	}
);
	
ITHit.Add('HtmlDecode',
	function (sText) {
		return sText.replace(/&quot;/, '"').replace(/&amp;/g, '\'').replace(/&gt;/g, '>').replace(/&lt;/g, '<');
	}
);

ITHit.Add('Encode',
	function(sText) {
		
		if (!sText) {
			return sText;
		}
		
		return ITHit.EncodeURI(sText.replace(/%/g,  "%25"))
			.replace(/~/g,  "%7E")
			.replace(/!/g,  "%21")
			.replace(/@/g,  "%40")
			.replace(/#/g,  "%23")
			.replace(/\$/g, "%24")
			.replace(/&/g,  "%26")
			.replace(/\*/g, "%2A")
			.replace(/\(/g, "%28")
			.replace(/\)/g, "%29")
			.replace(/\-/g, "%2D")
			.replace(/_/g,  "%5F")
			.replace(/\+/g, "%2B")
			.replace(/\=/g, "%3D")
			.replace(/'/g,  "%27")
			.replace(/;/g,  "%3B")
			.replace(/\,/g, "%2C")
			.replace(/\?/g, "%3F");
	}
);

ITHit.Add('EncodeURI',
	function(sText) {
		
		if (!sText) {
			return sText;
		}
		
		return encodeURI(sText).replace(/%25/g, "%");
	}
);

ITHit.Add('Decode',
	function(sText) {
		
		if (!sText) {
			return sText;
		}
		
		var sText = sText
			.replace(/%7E/gi, "~")
			.replace(/%21/g,  "!")
			.replace(/%40/g,  "@")
			.replace(/%23/g,  "#")
			.replace(/%24/g,  "$")
			.replace(/%26/g,  "&")
			.replace(/%2A/gi, "*")
			.replace(/%28/g,  "(")
			.replace(/%29/g,  ")")
			.replace(/%2D/gi, "-")
			.replace(/%5F/gi, "_")
			.replace(/%2B/gi, "+")
			.replace(/%3D/gi, "=")
			.replace(/%27/g,  "'")
			.replace(/%3B/gi, ";")
			.replace(/%2E/gi, ".")
			.replace(/%2C/gi, ",")
			.replace(/%3F/gi, "?");
		
		return ITHit.DecodeURI(sText);
	}
);

ITHit.Add('DecodeURI',
	function(sText) {
		
		if (!sText) {
			return sText;
		}
		
		return decodeURI(sText.replace(/%([^0-9A-F]|.(?:[^0-9A-F]|$)|$)/gi, "%25$1"));
	}
);

ITHit.Add('DecodeHost',
	function(sHref) {
		
		// Check whether host contains encoded characters.
		if (/^(http|https):\/\/[^:\/]*?%/.test(sHref)) {
			
			var aMatchRes = sHref.match(/^(?:http|https):\/\/[^\/:]+/);
			if (aMatchRes && aMatchRes[0]) {
				var sMatch = aMatchRes[0].replace(/^(http|https):\/\//, '');
				
				// Decode characters to prevent crossdomain restriction.
				sHref = sHref.replace(sMatch, ITHit.Decode(sMatch));
			}
		}
		
		return sHref;
	}
);

ITHit.Add('WebDAV.Client.LicenseId', null);

(function() {

	var fNoop = function() {
	};

	var extendWithSuper = function (childClass, newProperties) {
		// Extend and setup virtual methods
		for (var key in newProperties) {
			if (!newProperties.hasOwnProperty(key)) {
				continue;
			}

			var value = newProperties[key];
			if (typeof value == 'function' && typeof childClass[key] == 'function' && childClass[key] !== fNoop) {
				childClass[key] = coverVirtual(value, childClass[key]);
			} else {
				childClass[key] = value;
			}
		}

		// Default state
		if (!childClass._super) {
			childClass._super = fNoop;
		}
	};

	var coverVirtual = function (childMethod, parentMethod) {
		return function () {
			var old = this._super;
			this._super = parentMethod;
			var r = childMethod.apply(this, arguments);
			this._super = old;
			return r;
		};
	};

	var instanceUniqueCounter = 0;

	/**
	 * @name ITHit.DefineClass
	 * @param {String} globalName
	 * @param {Function} parentClass
	 * @param {Object} [prototypeProperties]
	 * @param {Object} [staticProperties]
	 */
	ITHit.Add('DefineClass', function (globalName, parentClass, prototypeProperties, staticProperties) {
		parentClass = parentClass !== null ? parentClass : function() {};

		if (!parentClass) {
			throw new Error('Not found extended class for ' + globalName);
		}

		if (prototypeProperties.hasOwnProperty('__static')) {
			staticProperties = prototypeProperties.__static;
			delete prototypeProperties.__static;
		}

		var childClass;

		// The constructor function for the new subclass is either defined by you
		// (the "constructor" property in your `extend` definition), or defaulted
		// by us to simply call the parent's constructor.
		if (prototypeProperties && prototypeProperties.hasOwnProperty('constructor')) {
			childClass = function() {
				this.__instanceName = this.__className + instanceUniqueCounter++;
				return coverVirtual(prototypeProperties.constructor, parentClass).apply(this, arguments);
			};
		} else {
			childClass = function () {
				this.__instanceName = this.__className + instanceUniqueCounter++;
				return parentClass.apply(this, arguments);
			};
		}

		// Add static properties to the constructor function, if supplied.
		for (var prop in parentClass) {
			childClass[prop] = parentClass[prop];
		}
		extendWithSuper(childClass, staticProperties);

		// Set the prototype chain to inherit from `parent`, without calling
		// `parent`'s constructor function.
		var Surrogate = function () {
			this.constructor = childClass;
		};
		Surrogate.prototype = parentClass.prototype;
		childClass.prototype = new Surrogate;

		// Clone empty objects
		for (var key in Surrogate.prototype) {
			if (!Surrogate.prototype.hasOwnProperty(key)) {
				continue;
			}

			var value = Surrogate.prototype[key];
			if (!value) {
				continue;
			}

			if (value instanceof Array) {
				if (value.length === 0) {
					childClass.prototype[key] = [];
				}
			} else if (typeof value === 'object') {
				var isEmpty = true;
				for (var k in value) {
					isEmpty = isEmpty && value.hasOwnProperty(k);
				}
				if (isEmpty) {
					childClass.prototype[key] = {};
				}
			}
		}

		// Add prototype properties (instance properties) to the subclass,
		// if supplied.
		if (prototypeProperties) extendWithSuper(childClass.prototype, prototypeProperties);

		// Share class name
		childClass.__className = childClass.prototype.__className = globalName;

		// Split namespace
		var iPos = globalName.lastIndexOf('.'),
			sLocalName = globalName.substr(iPos + 1);
		return ITHit.Declare(globalName.substr(0, iPos))[sLocalName] = childClass;
	});

})();

/*
 * Base namespace for exceptions.
 * @namespace ITHit.Exceptions
 */

/**
 * This namespace provides classes for accessing WebDAV server items, file structure management, properties management and items locking.
 * @namespace ITHit.WebDAV.Client
 */

/**
 * The ITHit.WebDav.Client.Exceptions namespace provides classes that represent various WebDAV client library exceptions, erroneous server responses and HTTP errors.
 * @namespace ITHit.WebDAV.Client.Exceptions
 */


ITHit.Temp.WebDAV_Phrases={
	CrossDomainRequestAttempt: 'Attempting to make cross-domain request.\nRoot URL: {0}\nDestination URL: {1}\nMethod: {2}',
	
	// WebDavRequest
	Exceptions: {
		BadRequest:         'The request could not be understood by the server due to malformed syntax.',
		Conflict:           'The request could not be carried because of conflict on server.',
		DependencyFailed:   'The method could not be performed on the resource because the requested action depended on another action and that action failed.',
		InsufficientStorage: 'The request could not be carried because of insufficient storage.',
		Forbidden:          'The server refused to fulfill the request.',
		Http:               'Exception during the request occurred.',
		Locked:             'The item is locked.',
		MethodNotAllowed:   'The method is not allowed.',
		NotFound:           'The item doesn\'t exist on the server.',
		PreconditionFailed: 'Precondition failed.',
		PropertyFailed:     'Failed to get one or more properties.',
		PropertyForbidden:  'Not enough rights to obtain one of requested properties.',
		PropertyNotFound:   'One or more properties not found.',
		Unauthorized:       'Incorrect credentials provided or insufficient permissions to access the requested item.',
		LockWrongCountParametersPassed: 'Lock.{0}: Wrong count of parameters passed. (Passed {1})',
		UnableToParseLockInfoResponse:  'Unable to parse response: quantity of LockInfo elements isn\'t equal to 1.',
		ParsingPropertiesException:     'Exception while parsing properties.',
		InvalidDepthValue: 'Invalid Depth value.',
		FailedCreateFolder: 'Failed creating folder.',
		FailedCreateFile: 'Failed creating file.',
		FolderWasExpectedAsDestinationForMoving: 'Folder was expected as destination for moving folder.',
		AddOrUpdatePropertyDavProhibition: 'Add or update of property {0} ignored: properties from "DAV:" namespace could not be updated/added.',
		DeletePropertyDavProhibition: 'Delete of property {0} ignored: properties from "DAV:" namespace could not be deleted.',
		NoPropertiesToManipulateWith: 'Calling UpdateProperties ignored: no properties to update/add/delete.',
		ActiveLockDoesntContainLockscope: 'Activelock node doesn\'t contain lockscope node.',
		ActiveLockDoesntContainDepth: 'Activelock node doedn\'t contain depth node.',
		WrongCountPropertyInputParameters: 'Wrong count of input parameters passed for Property constructor. Expected 1-3, passed: {1}.',
		FailedToWriteContentToFile: 'Failed to write content to file.',
		PropertyUpdateTypeException: 'Property expected to be an Property class instance.',
		PropertyDeleteTypeException: 'Property name expected to be an PropertyName class instance.',
		UnknownResourceType:  'Unknown resource type.',
		NotAllPropertiesReceivedForUploadProgress: 'Not all properties received for upload progress. {0}',
		ReportOnResourceItemWithParameterCalled: 'For files the method should be called without parametres.',
		WrongHref: 'Href expected to be a string.',
		WrongUploadedBytesType: 'Count of uploaded bytes expected to be a integer.',
		WrongContentLengthType: 'File content length expected to be a integer.',
		BytesUploadedIsMoreThanTotalFileContentLength: 'Bytes uploaded is more than total file content length.',
		ExceptionWhileParsingProperties: 'Exception while parsing properties.',
		IntegrationTimeoutException: 'Browser extention didnt fill data in {0} ms',
		FolderRewriteException: 'Rewrite of folders does not permitted.',
		NotFoundEventName: 'Not found event name `{0}`',
	},
	ResourceNotFound:         'Resource not found. {0}',
	ResponseItemNotFound:     'The response doesn\'t have required item. {0}',
	ResponseFileWrongType: 'Server returned folder while file is expected. {0}',
	FolderNotFound:           'Folder not found. {0}',
	ResponseFolderWrongType:  'Server returned file while folder is expected. {0}',
	ItemIsMovedOrDeleted:     'Cannot perform operation because item "{0}" is moved or deleted.',
	FailedToCopy:             'Failed to copy item.',
	FailedToCopyWithStatus:   'Copy failed with status {0}: {1}.',
	FailedToDelete:           'Failed to delete item.',
	DeleteFailedWithStatus:   'Delete failed with status {0}: {1}.',
	PutUnderVersionControlFailed: 'Put under version control failed.',
	FailedToMove:             'Failed to move item.',
	MoveFailedWithStatus:     'Move failed with status {0}: {1}.',
	UnlockFailedWithStatus:   'Unlock failed with status {0}: {1}.',
	PropfindFailedWithStatus: 'PROPFIND method failed with status {0}.',
	FailedToUpdateProp:       'Failed to update or delete one or more properties.',
	FromTo:                   'The From parameter cannot be less than To.',
	NotToken:                 'The supplied string is not a valid HTTP token.',
	RangeTooSmall:            'The From or To parameter cannot be less than 0.',
	RangeType:                'A different range specifier has already been added to this request.',
	ServerReturned:           'Server returned:',
	UserAgent:                'IT Hit WebDAV AJAX Library v{0}',
    FileUploadFailed:         'Failed to upload the file.',
    ProductName:              'IT Hit WebDAV AJAX Library',
	WrongParameterType:       'Wrong parameter type. Expected type is:{0}.',
	// WebDavResponse
	wdrs: {
		status: '\n{0} {1}',
		response: '{0}: {1}'
	}
};


;
(function () {
    /**
     * Detects environment in which JavaScript is running, such as operating system and web browser.
     * @api
     * @class ITHit.Environment
   */
    ITHit.DefineClass('ITHit.Environment', null,  /** @lends ITHit.Environment.prototype */{
        __static: /** @lends ITHit.Environment */{
            /**
             * Provides operating system name.
             * Could be: "Windows", "Linux", "MacOS", "UNIX", "IOS", "Android" or null if OS can not be detected.
             * @type {string}
             */
            OS: ITHit.DetectOS.OS
        }
    });
})();

ITHit.oNS = ITHit.Declare('ITHit.Exceptions');

/*
 * Exception for Logger class.
 * @class ITHit.Exceptions.LoggerException
 * @extends ITHit.Exception
 */
/*
 * Initializes a new instance of the LoggerException class with a specified error message and a reference to the inner exception that is the cause of this exception. 
 * @constructor LoggerException
 * 
 * @param {String} sMessage The error message string.
 * @param {optional ITHit.Exception} oInnerException The ITHit.Exception instance that caused the current exception.
 */
ITHit.oNS.LoggerException = function(sMessage, oInnerException) {
	
	// Inheritance definition.
	ITHit.Exceptions.LoggerException.baseConstructor.call(this, sMessage, oInnerException);
}

// Extend class.
ITHit.Extend(ITHit.oNS.LoggerException, ITHit.Exception);

// Exception name.
ITHit.oNS.LoggerException.prototype.Name = 'LoggerException';

/**
 * Type of information being logged.
 * @api
 * @enum {number}
 * @class ITHit.LogLevel
 */
ITHit.DefineClass('ITHit.LogLevel', null, {}, /** @lends ITHit.LogLevel */{

	/**
	 * All messages will be written to log.
	 * @type {number}
	 */
	All: 32,
	
	/**
	 * Messages with LogLevel.Debug level will be written to log.
	 * @type {number}
	 */
	Debug: 16,
	
	/**
	 * Messages with LogLevel.Info level will be written to log.
	 * @type {number}
	 */
	Info: 8,
	
	/**
	 * Messages with LogLevel.Warn level will be written to log.
	 * @type {number}
	 */
	Warn: 4,
	
	/**
	 * Messages with LogLevel.Error level will be written to log.
	 * @type {number}
	 */
	Error: 2,
	
	/**
	 * Messages with LogLevel.Fatal level will be written to log.
	 * @type {number}
	 */
	Fatal: 1,
	
	/**
	 * No messages will be written to log.
	 * @type {number}
	 */
	Off: 0
});


;
(function() {
	
	// Log listeners.
	var oListeners = {}
	
	// Declare counter for listeners
	var oListenersCount = {};
	
	// Declare all listeners listening each log level.
	var oListenersForLevels = {};
	
	// Initialize list of lesteners and counter.
	for (var sProp in ITHit.LogLevel) {
		oListeners[ITHit.LogLevel[sProp]]          = [];
		oListenersForLevels[ITHit.LogLevel[sProp]] = [];
	}

	var recheck = function(bIncrease, iFrom, iTo, fHandler) {

		for (var sProp in ITHit.LogLevel) {

			// Skip elements with higher log level.
			if (ITHit.LogLevel[sProp] > iTo) {
				continue;
			}

			// Skip elements with lower log level
			if (!ITHit.LogLevel[sProp]
				|| (iFrom >= ITHit.LogLevel[sProp])
			) {
				continue;
			}

			// Increase log level listeners list.
			if (bIncrease) {
				oListenersForLevels[ITHit.LogLevel[sProp]].push(fHandler);

				// Decrease log level listeners list.
			} else {
				for (var i = 0; i < oListenersForLevels[ITHit.LogLevel[sProp]].length; i++) {
					if (oListenersForLevels[ITHit.LogLevel[sProp]][i] == fHandler) {

						// Delete element from list.
						oListenersForLevels[ITHit.LogLevel[sProp]].splice(i, 1);
					}
				}
			}
		}

	};

	recheck.add = function(iTo, fHandler) {
		recheck.increase(ITHit.LogLevel.Off, iTo, fHandler);
	};

	recheck.del = function(iTo, fHandler) {
		recheck.decrease(ITHit.LogLevel.Off, iTo, fHandler);
	};

	recheck.increase = function(iFrom, iTo, fHandler) {
		recheck(true, iFrom, iTo, fHandler);
	};

	recheck.decrease = function(iFrom, iTo, fHandler) {
		recheck(false, iFrom, iTo, fHandler);
	};

	/**
	 * Provides static methods for logging.
	 * @api
	 * @class ITHit.Logger
	 */
	ITHit.DefineClass('ITHit.Logger', null, {}, /** @lends ITHit.Logger */{

		Level: ITHit.Config.LogLevel || ITHit.LogLevel.Debug,

		/**
		 * Handler function called when event is trigger.
		 * @callback ITHit.Logger~EventHandler
		 */

		/**
		 * Adds log listener.
		 * @api
		 * @param {ITHit.Logger~EventHandler} fHandler Handler function.
		 * @param {number} iLogLevel Log level messages capturing.
		 */
		AddListener: function (fHandler, iLogLevel) {

			// Delete listener from listeners list.
			if (iLogLevel == ITHit.LogLevel.Off) {
				this.RemoveListener();
			}

			// Initialize indexes.
			var iLevel = 0;
			var iIndex = 0;

			// Set outer loop exit lable.
			outer:
				// Loop through all log levels.
				for (var iProp in oListeners) {

					// Loop through all listeners for log level.
					for (var i = 0; i < oListeners[iProp].length; i++) {

						// If handler is found then save it's position for future comparison.
						if (oListeners[iProp][i] == fHandler) {

							// Save indexes for founded listener.
							iLevel = iProp;
							iIndex = i;

							// Break outer loop.
							break outer;
						}
					}
				}

			// Listener is not found.
			if (!iLevel) {

				// Add listener for specified log level.
				oListeners[iLogLevel].push(fHandler);

				recheck.add(iLogLevel, fHandler);

				// Listener has been found.
			} else {

				// If specified log level for listener is not the same.
				if (iLogLevel != iLevel) {

					// Delete listener for old log level.
					oListeners[iLevel].splice(iIndex, 1);

					// Declare listener for specified log level.
					oListeners[iLogLevel].push(fHandler);

					if (iLogLevel > iLevel) {
						recheck.increase(iLevel, iLogLevel, fHandler);
					} else {
						recheck.decrease(iLogLevel, iLevel, fHandler);
					}
				}
			}
		},

		/**
		 * Removes log listener.
		 * @api
		 * @param {ITHit.Logger~EventHandler} fHandler Handler function.
		 */
		RemoveListener: function (fHandler) {

			// Set lable for outer loop.
			outer:
				// Loop through all log levels.
				for (var iLogLevel in oListeners) {

					// Loop through all listeners for log level.
					for (var i = 0; i < oListeners[iLogLevel].length; i++) {

						// Listener is found.
						if (oListeners[iLogLevel][i] == fHandler) {

							// Delete specified listener.
							oListeners[iLogLevel].splice(i, 1);

							recheck.del(iLogLevel, fHandler);

							// Break outer loop.
							break outer;
						}
					}
				}

			return true;
		},

		/**
		 * Set log level for listener.
		 * @param fHandler
		 * @param iLogLevel
		 * @returns {*}
		 */
		SetLogLevel: function (fHandler, iLogLevel) {
			return this.AddListener(fHandler, iLogLevel, true);
		},

		/**
		 * Get log level for listener.
		 * @param fHandler
		 * @returns {*}
		 */
		GetLogLevel: function (fHandler) {

			// Loop through all log levels.
			for (var iLogLevel in oListeners) {

				// Loop through all listeners for log level.
				for (var i = 0; i < oListeners[iLogLevel].length; i++) {

					// Listener has been found.
					if (oListeners[iLogLevel][i] == fHandler) {

						// Return log level for specified listener..
						return iLogLevel;
					}
				}
			}

			// Listener has not been found in listeners list.
			return false;
		},

		/**
		 * Get listeners for specified log level.
		 * @param iLogLevel
		 * @returns {*}
		 */
		GetListenersForLogLevel: function (iLogLevel) {
			return oListenersForLevels[iLogLevel];
		},

		/**
		 * Get count of listeners for specified log level.
		 * @param iLogLevel
		 * @returns {*}
		 */
		GetCount: function (iLogLevel) {
			return oListenersForLevels[iLogLevel].length;
		},

		/**
		 * Writes response data to log if Level value is LogLevel.Info or higher.
		 *
		 * @param {Object} oResponse Response object.
		 */
		WriteResponse: function (oResponse) {

			// Check count of listeners for LogLevel.Info messages.
			if (Logger.GetCount(ITHit.LogLevel.Info)) {

				var sStr = '';

				// Add status and description data.
				if (oResponse instanceof HttpWebResponse) {
					sStr += '\n' + oResponse.StatusCode + ' ' + oResponse.StatusDescription + '\n';
				}

				// Add response URI.
				sStr += oResponse.ResponseUri + '\n';

				// Add all response headers.
				for (var sProp in oResponse.Headers) {
					sStr += sProp + ': ' + oResponse.Headers[sProp] + '\n';
				}

				// Add response body.
				sStr += oResponse.GetResponse();

				// Write response data to log.
				this.WriteMessage(sStr);
			}
		},

		/**
		 * Writs a message to log with a specified log level. Default log level is {@link ITHit.LogLevel#Info}
		 * @api
		 * @param {string} sMessage Message to be logged.
		 * @param {number} iLogLevel Logging level.
		 * @throws ITHit.Exceptions.LoggerException Function was expected as log listener.
		 */
		WriteMessage: function (sMessage, iLogLevel) {

			// Check log level.
			iLogLevel = ('undefined' == typeof iLogLevel) ? ITHit.LogLevel.Info : parseInt(iLogLevel);

			// Check whether there are listeners for current log level.
			if (ITHit.Logger.GetCount(iLogLevel)) {

				// Get listeners for current log level.
				var aListeners = this.GetListenersForLogLevel(iLogLevel);

				var sMessage = String(sMessage).replace(/([^\n])$/, '$1\n');

				// Loop through listeners.
				for (var i = 0; i < aListeners.length; i++) {
					try {
						// Pass message to lestener.
						aListeners[i](sMessage, ITHit.LogLevel.Info);
					} catch (e) {

						if (!aListeners[i] instanceof Function) {
							throw new ITHit.Exceptions.LoggerException('Log listener expected function, passed: "' + aListeners[i] + '"', e);
						} else {
							throw new ITHit.Exceptions.LoggerException('Message could\'not be logged.', e);
						}
					}
				}
			}
		},

		StartLogging: function () {
		},

		FinishLogging: function () {
		},

		StartRequest: function () {
			//this.WriteMessage('--- Request started ---', ITHit.LogLevel.Info);
		},

		FinishRequest: function () {
			//this.WriteMessage('--- Request finished ---', ITHit.LogLevel.Info);
		}
	});

})();

ITHit.oNS = ITHit.Declare('ITHit.Exceptions');

/*
 * Exception for Phrases class.
 * @class ITHit.Exceptions.PhraseException
 * @extends ITHit.Exception
 */
/*
 * Initializes a new instance of the PhraseException class with a specified error message and a reference to the inner exception that is the cause of this exception.
 * @constructor PhraseException
 * 
 * @param {String} sMessage The error message string.
 * @param {optional ITHit.Exception} oInnerException The ITHit.Exception instance that caused the current exception.
 */
ITHit.oNS.PhraseException = function(sMessage, oInnerException) {
	
	// Inheritance definition.
	ITHit.Exceptions.PhraseException.baseConstructor.call(this, sMessage, oInnerException);
}

// Extend class.
ITHit.Extend(ITHit.oNS.PhraseException, ITHit.Exception);

// Exception name.
ITHit.oNS.PhraseException.prototype.Name = 'PhraseException';

/*
 * Class for work with the text. Allows parse transferred JSON text and gives the convenient 
 *    mechanism for returning phrases with an opportunity of replacement placeholders.
 * @struct {static} ITHit.Phrases
 */
ITHit.Phrases = (function() {
	
	var PhrasesToEval = {};
	
	/*
	 * Class for replacing placeholders. Class for using with replace method.
	 * @class _callbackReplace
	 */
	/*
	 * Initializes a new instance of the _callbackReplace class.
	 * @constructor _callbackReplace
	 * 
	 * @param {Object} oArguments Phrases to replace.
	 */
	var _callbackReplace = function(oArguments) {
		this._arguments = oArguments;
	}
	/*
	 * Method for replacing placeholders.
	 * @function {private String} _callbackReplace.Replace
	 * 
	 * @param {String} sPlaceholder Placeholder for replacing.
	 * 
	 * @returns Sentence.
	 */
	_callbackReplace.prototype.Replace = function(sPlaceholder) {
		
		var iIndex = sPlaceholder.substr(1, sPlaceholder.length-2);
		return ('undefined' != typeof this._arguments[iIndex]) ? this._arguments[iIndex] : sPlaceholder;
	}
	
	var Phrase = function(sPhrase) {
		this._phrase = sPhrase;
	}
		
	/*
	 * Method for returning a phrase. It is implicitly caused at access to object in a context of a line.
	 * @function {String} ITHit.Phrases.Phrase.toString
	 *
	 * @returns Phrase.
	 */
	Phrase.prototype.toString = function() {
		return this._phrase;
	}

	/*
	 * A method for replacement placeholders. Accepts unlimited number of parameters for replacement.
	 * @function {String} ITHit.Phrases.Phrase.Paste
	 *
	 * @returns Phrase.
	 */
	Phrase.prototype.Paste = function() {
		
		var sPhrase = this._phrase;
		if (/\{\d+?\}/.test(sPhrase)) {
			var oReplace = new _callbackReplace(arguments);
			sPhrase = sPhrase.replace(/\{(\d+?)\}/g, function(args){return oReplace.Replace(args);});
		}
		
		return sPhrase;
	}
	
	var Phrases = function() {}
	
	/*
	 * A method for transformation JSON text into javascript object.
	 * @function {Boolean} ITHit.Phrases.loadJSON
	 * 
	 * @paramset Syntax 1
	 * @param {String} mPhrases A line containing JSON text of phrases.
	 * @param {optional String} sNamespace A way in which phrases will be stored. It is set in the form of: "name1.name2".
	 * @paramset Syntax 2
	 * @param {Object} mPhrases A line containing JSON object of phrases.
	 * @param {optional String} sNamespace A way in which phrases will be stored. It is set in the form of: "name1.name2".
	 * 
	 * @throws ITHit.Exceptions.PhraseException &nbsp;Wrong text structure if failed to eval passed JSON text or namespace expected to be a string.
	 */
	Phrases.prototype.LoadJSON = function(mPhrases, sNamespace) {
		
		var utilsNs = ITHit.Utils
		
		if ( sNamespace && !utilsNs.IsString(sNamespace) ) {
			throw new ITHit.Exceptions.PhraseException('Namespace expected to be a string.');
		}
		
		var _context = this;
		
		// Select or create context if specified.
		if (sNamespace) {
			_context = ITHit.Declare(sNamespace);
		}
		
		try {
			var oPhrases = mPhrases;
			
			// Eval JSON string to obtain an object.
			if (utilsNs.IsString(oPhrases)) {
				oPhrases = eval('('+ mPhrases +')');
			}
			
			this._AddPhrases(oPhrases, _context);
			
		} catch(e) {
			console.dir(e);
			throw new ITHit.Exceptions.PhraseException('Wrong text structure.', e);
		}
	}
	
	Phrases.prototype.LoadLocalizedJSON = function(defaultPhrases, localizedPhrases, namespace) {
		
		var utilsNs     = ITHit.Utils,
		    isUndefined = utilsNs.IsUndefined,
		    isObject    = utilsNs.IsObject;
		
		if (!defaultPhrases || !utilsNs.IsObjectStrict(defaultPhrases)) {
			throw new ITHit.Exceptions.PhraseException('Default phrases expected to be an JSON object.');
		}
		if (localizedPhrases && !utilsNs.IsObjectStrict(localizedPhrases)) {
			throw new ITHit.Exceptions.PhraseException('Default phrases expected to be an JSON object');
		}
		
		var mergedPhrases;
		if (localizedPhrases) {
			
			mergedPhrases = {};
			
			// Clone localized phrases.
			this._MergePhrases(mergedPhrases, localizedPhrases);
			
			// Add default phrases whether localized is not set.
			this._MergePhrases(mergedPhrases, defaultPhrases);
			
		} else {
			mergedPhrases = defaultPhrases;
		}
		
		this.LoadJSON(mergedPhrases, namespace);
	}
	
	Phrases.prototype._MergePhrases = function(dest, source) {
		
		var utilsNs     = ITHit.Utils,
		    isUndefined = utilsNs.IsUndefined,
		    isObject    = utilsNs.IsObject;
		
		for (var prop in source) {
			if (!source.hasOwnProperty(prop)) continue;
			
			if (isUndefined(dest[prop])) {
				dest[prop] = source[prop];
			} else if (isObject(dest[prop])) {
				this._MergePhrases(dest[prop], source[prop]);
			}
		}
	}
	
	/*
	 * A method for converting phrases into objects.
	 * @function {private} ITHit.Phrases._AddPhrases
	 * 
	 * @param {Object} oPhrases Phrase object.
	 * @param {Object} _context A way in which phrases will be stored.
	 *
	 * @throws ITHit.Exceptions.PhraseException &nbsp;Passed phrase is one of reserved words.
	 */
	Phrases.prototype._AddPhrases = function(oPhrases, _context) {
		
		// Get context.
		_context = _context || this;
		
		// Loop through phrases.
		for (var phrase in oPhrases) {
			if ( ('object' != typeof oPhrases[phrase]) || !(oPhrases[phrase] instanceof Object) ) {
				
				switch (phrase) {
					case '_AddPhrases':
					case 'LoadJSON':
					case 'LoadLocalizedJSON':
					case '_Merge':
					case 'prototype':
					case 'toString':
						throw new ITHit.Exceptions.PhraseException('"'+ phrase +'" is reserved word.');
						break;
				}
				
				_context[phrase] = new Phrase(oPhrases[phrase]);
			} else {
				this._AddPhrases(oPhrases[phrase], _context[phrase] ? _context[phrase] : (_context[phrase] = {}));
			}
		}
	}
	
	return new Phrases();
})();


ITHit.oNS = ITHit.Declare('ITHit.Exceptions');

/*
 * Exception for XPath class.
 * @class ITHit.Exceptions.XPathException
 * @extends ITHit.Exception
 */
/*
 * Initializes a new instance of the XPathException class with a specified error message and a reference to the inner exception that is the cause of this exception.
 * @constructor XMLDocException
 * 
 * @param {String} sMessage Variable name.
 * @param {optional ITHit.Exception} oInnerException The ITHit.Exception instance that caused the current exception.
 */
ITHit.oNS.XPathException = function(sMessage, oInnerException) {
	
	// Inheritance definition.
	ITHit.Exceptions.XPathException.baseConstructor.call(this, sMessage, oInnerException);
}

// Extend class.
ITHit.Extend(ITHit.oNS.XPathException, ITHit.Exception);

// Exception name.
ITHit.oNS.XPathException.prototype.Name = 'XPathException';

/*
 * XPath class.
 * @class ITHit.XPath
 */
ITHit.XPath = {
	_component: null,
	_version: null
};

/*
 * Static method for executing search.
 * @constructor XPath
 * 
 * @param {String} sExpression String expression for search.
 * @param {ITHit.XMLDoc} oXmlDom XML DOM object.
 * @param {optional ITHit.XPath.resolver} mResolver Namespace resolver object or null if namespace is not specified for search.
 * @param {optional ITHit.XPath.result} mResult Result object to reuse result object for search results or null for creating new result object.
 * 
 * @returns Result object or XML DOM element.
 * 
 * @throws ITHit.Exceptions.XPathException &nbsp;
 */
/*
 * @function {ITHit.XPath.result} ITHit.XPath
 */
ITHit.XPath.evaluate = function(sExpression, oXmlDom, oResolver, oResult, _bSelectSingle) {
	
	// Check whether variables has valid types.
	if ( ('string' != typeof sExpression) && !(sExpression instanceof String) ) {
		throw new ITHit.Exceptions.XPathException('Expression was expected to be a string in ITHit.XPath.eveluate.');
	}
	
	if ( !(oXmlDom instanceof ITHit.XMLDoc) ) {
		throw new ITHit.Exceptions.XPathException('Element was expected to be an ITHit.XMLDoc object in ITHit.XPath.evaluate.');
	}
	
	if ( oResolver && !(oResolver instanceof ITHit.XPath.resolver) ) {
		throw new ITHit.Exceptions.XPathException('Namespace resolver was expected to be an ITHit.XPath.resolver object in ITHit.XPath.evaluate.');
	}
	
	if ( oResult && !(oResult instanceof ITHit.XPath.result) ) {
		throw new ITHit.Exceptions.XPathException('Result expected to be an ITHit.XPath.result object in ITHit.XPath.evaluate.');
	}
	
	// Set default values if is not passed.
	oResolver = oResolver || null;
	oResult   = oResult   || null;
	
	if ( document.implementation.hasFeature('XPath', '3.0') && document.evaluate ) {
		
		// Get XML DOM Element.
		var oContext = oXmlDom._get();
		var oContextDocument = oContext.ownerDocument || oContext;
		
		// If specified then reuse result for search.
		if (oResult) {
			oContextDocument.evaluate(sExpression, oContext, oResolver, ITHit.XPath.result.UNORDERED_NODE_SNAPSHOT_TYPE, oResult._res);
			return;
		}
		
		// Return result set.
		var oRes = new ITHit.XPath.result(oContextDocument.evaluate(sExpression, oContext, oResolver, ITHit.XPath.result.UNORDERED_NODE_SNAPSHOT_TYPE, null));
		
		// Return result set.
		if (!_bSelectSingle) {
			return oRes;
			
		// Return single (first) result.
		} else {
			return oRes.iterateNext();
		}
	} else if (undefined !== window.ActiveXObject) {
			
		// Get XML DOM Element.
		var oContext = oXmlDom._get();
		
		// Check whether setProperty method is supported.
		var bIsSetProp = false;
		try {
			oContext.getProperty('SelectionNamespaces');
			bIsSetProp = true;
		} catch(e) {}
		
		var bChangedNs = false;
		if (3 == ITHit.XMLDoc._version) {
			
			var sXml = oContext.xml.replace(/^\s+|\s+$/g, '');
			
			// Data to replace.
			var sReplaceWhat = 'urn:uuid:c2f41010-65b3-11d1-a29f-00aa00c14882/';
			var sReplaceTo   = 'cutted';
			
			if ( -1 != sXml.indexOf(sReplaceWhat) || true) {
				
				// Make replace.
				var sXmlNew = sXml.replace(sReplaceWhat, sReplaceTo);
				
				// Create new XML DOM document.
				var oXmlDoc = new ITHit.XMLDoc();
				oXmlDoc.load(sXmlNew);
				
				// Make replace for namespace resolver.
				if (oResolver) {
					var oNs = oResolver.getAll();
					for (var sAlias in oNs) {
						if (sReplaceWhat == oNs[sAlias]) {
							oNs.add(sAlias, sReplaceTo); 
							break;
						}
					}
				}
				
				oContext   = oXmlDoc._get();
				bIsSetProp = true;
				bChangedNs = true;
			}
		}
		
		// Set namespaces.
		if ( bIsSetProp && oResolver && oResolver.length() ) {
			
			var oNsPairs = oResolver.getAll();
			var aNs = [];
			for (var sAlias in oNsPairs) {
				aNs.push("xmlns:"+ sAlias +"='"+ oNsPairs[sAlias] +"'");
			}
			
			oContext.setProperty("SelectionNamespaces", aNs.join(' '));
		}
		
		if (bChangedNs) {
			oContext = oContext.documentElement;
		}
		
		try {
			
			// Return result set.
			if (!_bSelectSingle) {
				
				// Return result.
				if (!oResult) {
					return new ITHit.XPath.result(oContext.selectNodes(sExpression));
					
				// Reuse result object.
				} else {
					oResult._res = oContext.selectNodes(sExpression);
					return;
				}
				
			// Return single result.
			} else {
				
				// Search single element.
				var mOut = oContext.selectSingleNode(sExpression);
				
				if (mOut) {
					return new ITHit.XMLDoc(mOut);
				} else {
					return mOut;
				}
			}
			
		} catch(e) {
			
			// Check whether XML Document needed to be created.
			if ( !bIsSetProp
				&& (-2147467259 == e.number) // This object is a Microsoft extension and is only supported in Internet Explorer.
				&& oResolver
				&& oResolver.length()
			) {
				
				// Create new XML Document with passed XML Dom nodes.
				var sEl = new ITHit.XMLDoc(oContext).toString();
				var oEl = new ITHit.XMLDoc();
				oEl.load(sEl);
				oContext = oEl._get();
				
				// Set namespace resolver.
				var oNsPairs = oResolver.getAll();
				var aNs = [];
				for (var sAlias in oNsPairs) {
					aNs.push("xmlns:"+ sAlias +"='"+ oNsPairs[sAlias] +"'");
				}
				oContext.setProperty("SelectionNamespaces", aNs.join(' '));
				
				// Get document element.
				oContext = oContext.documentElement;
				
				// Return result set.
				if (!_bSelectSingle) {
					
					// Return result.
					if (!oResult) {
						return new ITHit.XPath.result(oContext.selectNodes(sExpression));
						
					// Reuse result object.
					} else {
						oResult._res = oContext.selectNodes(sExpression);
						return;
					}
					
				// Return single result.
				} else {
					
					// Search single element.
					var mOut = oContext.selectSingleNode(sExpression);
					
					if (mOut) {
						return new ITHit.XMLDoc(mOut);
					} else {
						return mOut;
					}
				}
				
			// Throw exception otherwise.
			} else {
				throw new ITHit.Exceptions.XPathException('Evaluation failed for searching "'+ sExpression +'".', e);
			}
		}
	}
	
	throw new ITHit.Exceptions.XPathException('XPath support is not implemented for your browser.');
}

/*
 * Find single (first) node.
 * @function {ITHit.XMLDoc} ITHit.XPath.selectSingleNode
 * 
 * @param {String} sExpression String expression for search.
 * @param {ITHit.XMLDoc} oXmlDom XML DOM object.
 * @param {optional ITHit.XPath.resolver} mResolver Namespace resolver object or null if namespace is not specified for search.
 */
ITHit.XPath.selectSingleNode = function(sExpression, oXmlDom, oResolver) {
	return ITHit.XPath.evaluate(sExpression, oXmlDom, oResolver, false, true);
}

/*
 * Class for creating namespace resolver for XPath.
 * @class ITHit.XPath.resolver
 */
/*
 * Create new instance of resolver class.
 * @constructor resolver
 */
ITHit.XPath.resolver = function() {
	this._ns     = {};
	this._length = 0;
}

/*
 * Add alias and namespace for it.
 * @function ITHit.XPath.resolver.add
 * 
 * @param {String} sAlias Namespace alias.
 * @param {String} sNs Namespace
 */
ITHit.XPath.resolver.prototype.add = function(sAlias, sNs) {
	this._ns[sAlias] = sNs;
	this._length++;
}

/*
 * Removes alias and namespace corresponding to it.
 * @function ITHit.XPath.resolver.remove
 * 
 * @param {String} sAlias Alias for namespace to delete.
 */
ITHit.XPath.resolver.prototype.remove = function(sAlias) {
	delete this._ns[sAlias];
	this._length--;
}

/*
 * Get namespace corresponding to passed alias.
 * @function {String} ITHit.XPath.resolver.get
 *  
 * @param {String} sAlias Alias for namespace.
 * 
 * @returns Corresponding to alias namespace.
 */
ITHit.XPath.resolver.prototype.get = function(sAlias) {
	return this._ns[sAlias] || null;
}

/*
 * Alias for get method.
 * @function {String} ITHit.XPath.resolver.lookupNamespaceURI
 * 
 * @see ITHit.XPath.resolver.get
 */
ITHit.XPath.resolver.prototype.lookupNamespaceURI = ITHit.XPath.resolver.prototype.get;

/*
 * Get list of all namespaces.
 * @function {Object} ITHit.XPath.resolver.getAll
 * 
 * @returns List of aliases as keys and corresponding to it namespaces.
 */
ITHit.XPath.resolver.prototype.getAll = function() {
	
	var oOut = {};
	for (var sAlias in this._ns) {
		oOut[sAlias] = this._ns[sAlias];
	}
	
	return oOut;
}

/*
 * Get count of setted namespaces.
 * @function {Integer} ITHit.XPath.resolver.length
 * 
 * @returns Count of added alias and namespace pairs.
 */
ITHit.XPath.resolver.prototype.length = function() {
	return this._length;
}

/*
 * Class representing result of XPath query.
 * @class ITHit.XPath.resolver.result
 */
/*
 * Create new instance of result class.
 * @constructor result
 * 
 * @param {Object} oResult XPath result object.
 */
ITHit.XPath.result = function(oResult) {
	this._res = oResult;
	this._i   = 0;
	this.length = oResult.length ? oResult.length : oResult.snapshotLength;
}

/*
 * Constants representing result type.
 */
ITHit.XPath.result.ANY_TYPE                     = 0;
ITHit.XPath.result.NUMBER_TYPE                  = 1;
ITHit.XPath.result.STRING_TYPE                  = 2;
ITHit.XPath.result.BOOLEAN_TYPE                 = 3;
ITHit.XPath.result.UNORDERED_NODE_ITERATOR_TYPE = 4;
ITHit.XPath.result.ORDERED_NODE_ITERATOR_TYPE   = 5;
ITHit.XPath.result.UNORDERED_NODE_SNAPSHOT_TYPE = 6;
ITHit.XPath.result.ORDERED_NODE_SNAPSHOT_TYPE   = 7;
ITHit.XPath.result.ANY_UNORDERED_NODE_TYPE      = 8;
ITHit.XPath.result.FIRST_ORDERED_NODE_TYPE      = 9;

/*
 * Iterate through founded nodes.
 * @function ITHit.XPath.resolver.iterateNext
 * 
 * @returns Result value.
 */
ITHit.XPath.result.prototype.iterateNext = function(iIndex) {
	
	var mOut;
	if (!iIndex) {
		if (!this._res.snapshotItem) {
			try {
				mOut = this._res[this._i++];
			} catch(e) {
				return null;
			}
		} else {
			mOut = this._res.snapshotItem(this._i++);
		}
	} else {
		mOut = this._res[iIndex];
	}
	
	if (mOut) {
		return new ITHit.XMLDoc(mOut);
	} else {
		return mOut;
	}
}

/*
 * Iterate through founded nodes.
 * @function ITHit.XPath.resolver.snapshotItem
 * 
 * @param {Integer} iIndex for result node for snapshot result type.
 * 
 * @returns Result value.
 */
ITHit.XPath.result.prototype.snapshotItem = ITHit.XPath.result.prototype.iterateNext;

/*
 * Return type for result.
 * @function {Integer} ITHit.XPath.resolver.type
 * 
 * @returns Result type.
 */
ITHit.XPath.result.prototype.type = function() {
	return this._res.resultType;
}

ITHit.XPath.result.prototype._get = function() {
	return this._res;
}


ITHit.oNS = ITHit.Declare('ITHit.Exceptions');

/*
 * Exception for XMLDoc class.
 * @class ITHit.Exceptions.XMLDocException
 * @extends ITHit.Exception
 */
/*
 * Initializes a new instance of the XMLDocException class with a specified error message and a reference to the inner exception that is the cause of this exception.
 * @constructor XMLDocException
 * 
 * @param {String} sMessage Variable name.
 * @param {optional ITHit.Exception} oInnerException The ITHit.Exception instance that caused the current exception.
 */
ITHit.oNS.XMLDocException = function(sMessage, oInnerException) {
	
	// Inheritance definition.
	ITHit.Exceptions.XMLDocException.baseConstructor.call(this, sMessage, oInnerException);
}

// Extend class.
ITHit.Extend(ITHit.oNS.XMLDocException, ITHit.Exception);

// Exception name.
ITHit.oNS.XMLDocException.prototype.Name = 'XMLDocException';

/*
 * Class for manipulating XML document.
 * @class ITHit.XMLDoc
 */
ITHit.XMLDoc = (function() {
	
	/*
	 * Holds AxtiveX Object GUID.
	 * @property {private String} ITHit.XMLDoc._actXObj
	 */
	var _actXObj;
	
	// Node types
	var NODE_ELEMENT = 1;
	var NODE_ATTRIBUTE = 2;
	var NODE_TEXT = 3;
	var NODE_CDATA_SECTION = 4;
	var NODE_ENTITY_REFERENCE = 5;
	var NODE_ENTITY = 6;
	var NODE_PROCESSING_INSTRUCTION = 7;
	var NODE_COMMENT = 8;
	var NODE_DOCUMENT = 9;
	var NODE_DOCUMENT_TYPE = 10;
	var NODE_DOCUMENT_FRAGMENT = 11;
	var NODE_NOTATION = 12;
	
	/*
	 * Creates class for working with XML documents.
	 * @constructor XMLDoc
	 * 
	 * @param {optional Object} oDomElem XML DOM element.
	 */
	var XMLDoc = function(oDomElem) {
		
		this._xml      = null;
		this._encoding = null;
		
		// Whether oDomElem is not null.
		if (null !== oDomElem) {
			
		// If oXmlObj is not passed then create XML document.
		if ( !oDomElem || ('object' != typeof oDomElem) ) {
			
			// Create document in IE.
		    if (undefined !== window.ActiveXObject) {
			
				// Whether activeX object is already have been initialized.
				if (_actXObj) {
					
					// Create instance of the same guid.
					this._xml = new window.ActiveXObject(_actXObj);
					
				// First initialization.
				} else {
					
					// Array of GUIDs for creating XML DOM document.
					var aComponents = ['Msxml2.DOMDocument.6.0', 'Msxml2.DOMDocument.4.0', 'Msxml2.DOMDocument.3.0'];
					var aVers       = [6, 4, 3]
					for (var i = 0; i < aComponents.length; i++) {
						try {
							this._xml = new window.ActiveXObject(aComponents[i]);
							
							// Save component's version.
							XMLDoc._version = aVers[i];
							
							// Save curent GUID for future instances.
							_actXObj = aComponents[i];
							
							break;
						} catch(e) {
							if (3 == aVers[i]) {
								throw new ITHit.Exception('XML component is not supported.');
							}
						}
					}
				}
			
			// Create XML document in Gecko based brousers.
			} else if (document.implementation && document.implementation.createDocument) {
				this._xml = document.implementation.createDocument('', '', null);
			}
			
			// Check whether XML document is not created.
			if (undefined === this._xml) {
				throw new ITHit.Exceptions.XMLDocException('XML support for current browser is not implemented.');
			}
			
			// Set XML document load to asyncronous mode.
			this._xml.async = false;
		
		// Assign passed XML element.
		} else {
			this._xml = oDomElem;
		}
			
		} else {
			this._xml = null;
			return null;
		}
	};
	
	/*
	 * Holds version of XML DOM GUID.
	 * @param {Inreger} ITHit.XMLDoc._version
	 */
	XMLDoc._version = 0;
	
	XMLDoc.prototype.contentEncoding = function(sEncoding) {
		if (undefined !== sEncoding) {
			this._encoding = sEncoding;
		}
		
		return this._encoding;
	}
	
	/*
	 * Load XML structure from string to specified object.
	 *  Previous structure will be deleted.
	 * @function ITHit.XMLDoc.load
	 * 
	 * @param {String} sXmlText XML string structure.
	 * 
	 * @throws ITHit.Exceptions.XMLDocException &nbsp;Srting was expected as parameter for method or wrong xml structure.
	 */
	XMLDoc.prototype.load = function(sXmlText) {
		
		if ( !ITHit.Utils.IsString(sXmlText) ) {
			throw new ITHit.Exceptions.XMLDocException('String was expected for xml parsing.');
		}
		
		if (!sXmlText) {
			return new XMLDoc();
		}
		
		var oDoc;
		
		// MSIE.
		if (undefined !== window.ActiveXObject) {
			try {
				
				// Replace unsupported in Msxml2.DOMDocument.3.0 namespace. 
				if (3 == XMLDoc._version) {
					sXmlText = sXmlText.replace(/(?:urn\:uuid\:c2f41010\-65b3\-11d1\-a29f\-00aa00c14882\/)/g, 'cutted');
				}
				
				if (XMLDoc._version) {
					sXmlText = sXmlText.replace(/<\?.*\?>/, '');	// for IE remove <?xml version="1.0" ?>
					this._xml.loadXML(sXmlText);
				} else {
					
					// Create new XML DOM document.
					var oXmlDoc = new XMLDoc();
					
					// Replace unsupported in Msxml2.DOMDocument.3.0 namespace.
					if (3 == XMLDoc._version) {
						sXmlText = sXmlText.replace(/(?:urn\:uuid\:c2f41010\-65b3\-11d1\-a29f\-00aa00c14882\/)/g, 'cutted');
					}
					
					// Load XML string.
					oXmlDoc.load(sXmlText);
					
					// Assign XML DOM to current object.
					this._xml = oXmlDoc._get();
				}
				
			} catch (e) {
				var oError = e;
			}
			
		// Mozilla and Netscape browsers.
		} else if (document.implementation.createDocument) {
			try {
				var oParser = new DOMParser();
				oDoc = oParser.parseFromString(sXmlText, "text/xml");
				this._xml = oDoc;
			} catch (e) {
				var oError = e;
			}
			
		} else {
			throw new ITHit.Exceptions.XMLDocException('Cannot create XML parser object. Support for current browser is not implemented.');
		}
		
		// If error while parsing happend.
		if (undefined !== oError) {
			throw new ITHit.Exceptions.XMLDocException('ITHit.XMLDoc.load() method failed.\nPossible reason: syntax error in passed XML string.', oError);
		}
	};
	
	/*
	 * Append child element.
	 * @function ITHit.XMLDoc.appendChild
	 * 
	 * @param {Object} oNode XML Dom element witch will be assigned to the current node.
	 * 
	 * @returns ITHit.Exceptions.XMLDocException Instance of XMLDoc class was expexted as parametr.
	 */
	XMLDoc.prototype.appendChild = function(oNode) {
		
		if (!oNode instanceof ITHit.XMLDoc) {
			throw ITHit.Exceptions.XMLDocException('Instance of XMLDoc was expected in appendChild method.');
		}
		
		this._xml.appendChild(oNode._get());
	};
	
	/*
	 * Create element method.
	 * @function {ITHit.XMLDoc} ITHit.XMLDoc.createElement
	 * 
	 * @param {String} sElementName Element name.
	 * 
	 * @returns XML DOM element.
	 */
	XMLDoc.prototype.createElement = function(sElementName) {
		return new XMLDoc(this._xml.createElement(sElementName));
	};
	
	/*
	 * Create element with namespace.
	 * @function {ITHit.XMLDoc} ITHit.XMLDoc.createElementNS
	 * 
	 * @param {String} sNS The URI of the namespace.
	 * @param {String} sElementName The qualified name of the element, as prefix:tagname.
	 * 
	 * @returns XML DOM element.
	 * 
	 * @throws ITHit.Exceptions.XMLDocException &nbsp;Node is not created.
	 */
	XMLDoc.prototype.createElementNS = function(sNS, sElementName) {
		
		// For Gecko based browsers
		if (this._xml.createElementNS) {
			var oElement = this._xml.createElementNS(sNS, sElementName);
						
			// Return new XML DOM element
			return new ITHit.XMLDoc(oElement);
		
		// For IE
		} else {
			try {
				return new XMLDoc(this._xml.createNode(NODE_ELEMENT, sElementName, sNS));
			} catch(e) {
				throw new ITHit.Exceptions.XMLDocException('Node is not created.', e);
			}
		}
		
		throw new ITHit.Exceptions.XMLDocException('createElementNS for current browser is not implemented.');
	};
	
	/*
	 * Create text node.
	 * @function {ITHit.XMLDoc} ITHit.XMLDoc.createTextNode
	 * 
	 * @param {String} sText Text.
	 * 
	 * @returns XML DOM text element.
	 */
	XMLDoc.prototype.createTextNode = function(sText) {
		return new XMLDoc(this._xml.createTextNode(sText));
	};
	
	/*
	 * Get element by it's id.
	 * @function {ITHit.XMLDoc} ITHit.XMLDoc.getElementById
	 * 
	 * @param {String} sId ID of the element.
	 * 
	 * @returns Selected element.
	 */
	XMLDoc.prototype.getElementById = function(sId) {
		return new XMLDoc(this._xml.getElementById(sId));
	};
	
	/*
	 * Get elements by it's tag names
	 * @function {ITHit.XMLDoc[]} ITHit.XMLDoc.getElementsByTagName
	 * 
	 * @param {String} sTagName Tag name of the elements.
	 * 
	 * @returns List of XML DOM elements.
	 */
	XMLDoc.prototype.getElementsByTagName = function(sTagName) {
		return new XMLDoc(this._xml.getElementsByTagName(sTagName));
	};
	
	/*
	 * Get element's child nodes.
	 * @function {ITHit.XMLDoc[]} ITHit.XMLDoc.childNodes
	 * 
	 * @returns List of child nodes.
	 */
	XMLDoc.prototype.childNodes = function() {
		
		var oNodes    = this._xml.childNodes;
		var oRetNodes = [];
		
		for ( var i = 0; i < oNodes.length; i++ ) {
			oRetNodes.push(new ITHit.XMLDoc(oNodes[i]));
		}
		
		return oRetNodes;
	}
	
	/*
	 * Get elements by it's tag names with namespace.
	 * @function {ITHit.XMLDoc[]} ITHit.XMLDoc.getElementsByTagNameNS
	 * 
	 * @param {String} sNamespace Element's namespace.
	 * @param {String} sTagName Tag name.
	 * 
	 * @returns List of selected nodes.
	 */
	XMLDoc.prototype.getElementsByTagNameNS = function(sNamespace, sTagName) {
		
		if (this._xml.getElementsByTagNameNS) {
			var oNode = this._xml.getElementsByTagNameNS(sNamespace, sTagName);
			
		} else {
			// Recreate XML DOM document.
			var sElem = this.toString();
			var oXmlDoc = new ITHit.XMLDoc();
			oXmlDoc.load(sElem);
			
			// Add namespace resolver.
			var oResolver = new ITHit.XPath.resolver();
			oResolver.add('a', sNamespace);
			
			// Search corresponding nodes.
			var oRes = ITHit.XPath.evaluate(('//a:'+ sTagName), oXmlDoc, oResolver);
			var oNode = oRes._get();
		}
		
		var aRet = [];
		for (var i = 0; i < oNode.length; i++) {
			var oNodeI = new ITHit.XMLDoc(oNode[i]);
			aRet.push(oNodeI);
		}
		
		return aRet;
	};
	
	/*
	 * Set attribute.
	 * @function ITHit.XMLDoc.setAttribute
	 * 
	 * @paramset Syntax 1
	 * @param {String} sName Attribute's name.
	 * @param {String} mValue Atribute's value.
	 * @paramset Syntax 2
	 * @param {String} sName Attribute's name.
	 * @param {Number} mValue Atribute's value.
	 */
	XMLDoc.prototype.setAttribute = function(sName, mValue) {
		this._xml.setAttribute(sName, mValue);
	};
	
	/*
	 * Check whether attribute with specified name is present in element's attributes list.
	 * @function {Boolean} ITHit.XMLDoc.hasAttribute
	 * 
	 * @param {String} sName Attribute's name.
	 * 
	 * @returns true if present, false otherwise.
	 */
	XMLDoc.prototype.hasAttribute = function(sName) {
		
		return this._xml.hasAttribute(sName);
	};
	
	/*
	 * Get attribute represented by name.
	 * @function {String} ITHit.XMLDoc.getAttribute
	 * 
	 * @param {String} sName Attribute's name.
	 * 
	 * @returns Value of the attribute or 'undefined' if attribute is not set.
	 */
	XMLDoc.prototype.getAttribute = function(sName) {
		
		return this._xml.getAttribute(sName);
	};
	
	/*
	 * Remove specified attribute.
	 * @function ITHit.XMLDoc.removeAttribute
	 * 
	 * @param {String} sName Attribute's name.
	 */
	XMLDoc.prototype.removeAttribute = function(sName) {
		
		this._xml.removeAttribute(sName);
	};
	
	/*
	 * Check whether attribute with specified name is present in element's attributes list.
	 * @function {Boolean} ITHit.XMLDoc.hasAttributeNS
	 * 
	 * @param {String} sName Attribute's name.
	 * 
	 * @returns true if present, false otherwise.
	 */
	XMLDoc.prototype.hasAttributeNS = function(sName) {
		
		return this._xml.hasAttribute(sName);
	};
	
	/*
	 * Get attribute represented by name.
	 * @function {String} ITHit.XMLDoc.getAttributeNS
	 * 
	 * @param {String} sName Attribute's name.
	 * 
	 * @returna Value of the attribute or 'undefined' if attribute is not set.
	 */
	XMLDoc.prototype.getAttributeNS = function(sName) {
		
		return this._xml.getAttribute(sName);
	};
	
	/*
	 * Remove specified attribute.
	 * @function ITHit.XMLDoc.removeAttributeNS
	 * 
	 * @param {String} sName Attribute's name.
	 */
	XMLDoc.prototype.removeAttributeNS = function(sName) {
		this._xml.removeAttribute(sName);
	};
	
	/*
	 * Remove specified child node with all it's subnodes from current XML DOM tree.
	 * @function {ITHit.XMLDoc} ITHit.XMLDoc.removeChild
	 * 
	 * @param {ITHit.XMLDoc} oNode Node for deleting.
	 * 
	 * @returns Deleted element.
	 * 
	 * @throws ITHit.Exceptions.XMLDocException &nbsp;Instance of XMLDoc was expected as method parameter.
	 */
	XMLDoc.prototype.removeChild = function(oNode) {
		
		if (!oNode instanceof ITHit.XMLDoc) {
			throw ITHit.Exceptions.XMLDocException('Instance of XMLDoc was expected in ITHit.XMLDoc.removeChild() method.');
		}
		
		this._xml.removeChild(oNode);
		
		return new ITHit.XMLDoc(oNode);
	};
	
	/*
	 * Remove specified node with all it's subnodes from current XML DOM tree.
	 * @function {ITHit.XMLDoc} ITHit.XMLDoc.removeNode
	 * 
	 * @param {ITHit.XMLDoc} oNode Node for deleting.
	 * 
	 * @returns Deleted element.
	 * 
	 * @throws ITHit.Exceptions.XMLDocException &nbsp;Instance of XMLDoc was expected as method parameter.
	 */
	XMLDoc.prototype.removeNode = function(oNode) {
		
		if (!oNode instanceof ITHit.XMLDoc) {
			throw ITHit.Exceptions.XMLDocException('Instance of XMLDoc was expected in ITHit.XMLDoc.removeNode() method.');
		}
		
		oNode = oNode._get();
		
		if (oNode.removeNode) {
			return new XMLDoc(oNode.removeNode(true));
		} else {
			return new XMLDoc(oNode.parentNode.removeChild(oNode));
		}
	};
	
	/*
	 * Clone specified node.
	 * @function {ITHit.XMLDoc} ITHit.XMLDoc.cloneNode
	 * 
	 * @param {ITHit.XMLDoc} oNode Node for cloning.
	 * @param {Boolean} bWithChildren Whether node be cloned with all it's subnodes.
	 * 
	 * @returns Cloned element.
	 * 
	 * @throws ITHit.Exceptions.XMLDocException &nbsp;Instance of XMLDoc was expected as method parameter.
	 */
	XMLDoc.prototype.cloneNode = function(bWithChildren) {
		
		if (undefined === bWithChildren) {
			bWithChildren = true;
		}
		
		return new ITHit.XMLDoc(this._xml.cloneNode(bWithChildren));
	};
	
	/*
	 * Get specified property.
	 * @function {String} ITHit.XMLDoc.getProperty
	 * 
	 * @param {String} sPropName Property name.
	 * 
	 * @returns Property value.
	 */
	XMLDoc.prototype.getProperty = function(sPropName) {
		return this._xml[sPropName];
	};
	
	/*
	 * Set specified property.
	 * @function {String} ITHit.XMLDoc.setProperty
	 * 
	 * @param {String} sPropName Property name.
	 * @param {String, Number} mValue Property value.
	 */
	XMLDoc.prototype.setProperty = function(sPropName, mValue) {
		this._xml[sPropName] = mValue;
	};
	
	/*
	 * Get node name with nprefix if specified.
	 * @function {String} ITHit.XMLDoc.nodeName
	 * 
	 * @returns Node name.
	 */
	XMLDoc.prototype.nodeName = function() {
		return this._xml.nodeName;
	};
	
	/*
	 * Get next sibling.
	 * @function {ITHit.XMLDoc} ITHit.XMLDoc.nextSibling
	 * 
	 * @returns Next sibling.
	 */
	XMLDoc.prototype.nextSibling = function() {
		return new ITHit.XMLDoc(this._xml.nextSibling);
	};
	
	/*
	 * Get element's namespace.
	 * @function {String} ITHit.XMLDoc.namespaceURI
	 * 
	 * @returns Element's namespace.
	 */
	XMLDoc.prototype.namespaceURI = function() {
		return this._xml.namespaceURI;
	};
	
	/*
	 * Whether element has child nodes.
	 *  @function {Boolean} ITHit.XMLDoc.hasChildNodes
	 *  
	 *  @returns true if element has child nodes, false otherwise.
	 */
	XMLDoc.prototype.hasChildNodes = function() {
		return (this._xml && this._xml.hasChildNodes());
	}
	
	/*
	 * Get first child node.
	 * @function {ITHit.XMLDoc} ITHit.XMLDoc.firstChild
	 * 
	 * @returns First child node.
	 */
	XMLDoc.prototype.firstChild = function() {
		return new XMLDoc(this._xml.firstChild);
	}
	
	/*
	 * Get local name (without prefix).
	 * @function {String} ITHit.XMLDoc.localName
	 * 
	 * @returns Element's name.
	 */
	XMLDoc.prototype.localName = function() {
		return this._xml.localName || this._xml.baseName;
	};
	
	/*
	 * Get node value.
	 * @function ITHit.XMLDoc.nodeValue
	 * 
	 * @returns Node's value.
	 */
	XMLDoc.prototype.nodeValue = function() {
		
		var mValue = '';
			
		if (this._xml) {
			mValue = this._xml.nodeValue;
		}
		
		if ('object' != typeof mValue) {
			return mValue;
		} else {
			return new ITHit.XMLDoc(mValue);
		}
	};
	
	/*
	 * Get node type.
	 * @function ITHit.XMLDoc.nodeType
	 * 
	 * @return Node's type.
	 */
	XMLDoc.prototype.nodeType = function() {
		return this._xml.nodeType;
	}
	
	XMLDoc.prototype._get = function() {
		return this._xml;
	};
	
	/*
	 * Returns XML DOM document as string. 
	 * @function {String} ITHit.XMLDoc.toString
	 * 
	 * @returns String representation of XML DOM element.
	 */
	XMLDoc.prototype.toString = function(bWithoutDeclaration) {
		return XMLDoc.toString(this._xml, this._encoding, bWithoutDeclaration);
	};
	
	/*
	 * Returns XML DOM document as string. Static method.
	 * @function {static String} ITHit.XMLDoc.toString
	 * 
	 * @returns String representation of XML DOM element.
	 */
	XMLDoc.toString = function(oXmlObj, sEncoding, bWithoutDeclaration) {
		
		if (!oXmlObj) {
			throw new ITHit.Exceptions.XMLDocException('ITHit.XMLDoc: XML object expected.');
		}
		
		var sOutput = '';
		var bRaiseException = true;
		
		// Check whether IE conversion method.
		if (undefined !== oXmlObj.xml) {
			sOutput = oXmlObj.xml.replace(/^\s+|\s+$/g, '');
			bRaiseException = false;
			
		// Check for XMLSerializer support by browser.
		} else if (document.implementation.createDocument && (undefined !== XMLSerializer)) {
			sOutput = new XMLSerializer().serializeToString(oXmlObj);
			bRaiseException = false;
		}
		
		// Check for output data.
		if (sOutput) {
			
			// Whether encoding is specified.
			if (sEncoding) {
				// Add encoding data.
				sEncoding = ' encoding="'+ this._encoding +'"'
			} else {
				// Clear encoding.
				sEncoding = '';
			}
			
			// Return string XML document.
			var sOut = ( (!bWithoutDeclaration) ? '<?xml version="1.0"'+ sEncoding +'?>' : '' )+ sOutput.replace(/^<\?xml[^?]+\?>/, ''); // Replace xml declaration if is set.
			
			return sOut;
		}
		
		if (bRaiseException) {
			throw new ITHit.Exceptions.XMLDocException('XML parser object is not created.');
		}
		
		return sOutput;
	};
	
	// Return reference of the constructor for the XMLDoc class.
	return XMLDoc;
})();

/*
 * XML DOM node types
 */
ITHit.XMLDoc.nodeTypes = {
	NODE_ELEMENT: 1,
	NODE_ATTRIBUTE: 2,
	NODE_TEXT: 3,
	NODE_CDATA_SECTION: 4,
	NODE_ENTITY_REFERENCE: 5,
	NODE_ENTITY: 6,
	NODE_PROCESSING_INSTRUCTION: 7,
	NODE_COMMENT: 8,
	NODE_DOCUMENT: 9,
	NODE_DOCUMENT_TYPE: 10,
	NODE_DOCUMENT_FRAGMENT: 11,
	NODE_NOTATION: 12
};

ITHit.oNS = ITHit.Declare('ITHit.Exceptions');

/*
 * Wrong argument value.
 * @class ITHit.Exceptions.ArgumentNullException
 * @extends ITHit.Exception
 */
/*
 * Initializes a new instance of the ArgumentNullException class with a variable name caused an exception.
 * @constructor ArgumentNullException
 * 
 * @param {String} sMessage Variable name.
 */
ITHit.oNS.ArgumentNullException = function(sVariable) {
	
	var sMessage = 'Variable "'+ sVariable +'" nas null value.';
	
	// Inheritance definition.
	ITHit.Exceptions.ArgumentNullException.baseConstructor.call(this, sMessage);
}

// Extend class.
ITHit.Extend(ITHit.oNS.ArgumentNullException, ITHit.Exception);

// Exception name.
ITHit.oNS.ArgumentNullException.prototype.Name = 'ArgumentNullException';

/**
 * Utilities container.
 * @class ITHit.WebDAV.Client.WebDavUtil
 */
ITHit.DefineClass('ITHit.WebDAV.Client.WebDavUtil', null, {
    __static: /** @lends ITHit.WebDAV.Client.WebDavUtil */{

        /**
		 * Check for non null value.
		 * @throws ITHit.Exceptions.ArgumentNullException Argument is null.
		 */
        VerifyArgumentNotNull: function (oArgument, sArgumentName) {
            if (oArgument === null) {
                throw new ITHit.Exceptions.ArgumentNullException(sArgumentName);
            }
        },

        /**
		 * Check for non empty and non null value.
		 * @throws ITHit.Exceptions.ArgumentNullException Argument is null or empty.
		 */
        VerifyArgumentNotNullOrEmpty: function (oArgument, sArgumentName) {
            if (oArgument === null || oArgument === '') {
                throw new ITHit.Exceptions.ArgumentNullException(sArgumentName);
            }
        },

        /**
		 * If oArgument is null or empty @return null 
		 */
        NormalizeEmptyToNull: function (oArgument) {
            if (oArgument === null || oArgument === '') {
                return null;
            }
            return oArgument;
        },

        /**
		 * If oArgument is null or empty or 'None' @return null 
		 */
        NormalizeEmptyOrNoneToNull: function (oArgument) {
            if (oArgument === null || oArgument === '' || oArgument == 'None') {
                return null;
            }
            return oArgument;
        },

        /**
		* Calculate string hash code @return string hash code
		*/
        HashCode: function (str) {
            var hash = 0;
            for (var i = 0; i < str.length; i++) {
                var character = str.charCodeAt(i);
                hash = ((hash << 5) - hash) + character;
                hash = hash & hash;
            }
            return hash;
        }
    }
});


ITHit.DefineClass('ITHit.WebDAV.Client.PropertyName', null, /** @lends ITHit.WebDAV.Client.PropertyName.prototype */{

	/**
	 * Name of the property.
	 * @api
	 * @type {string}
	 */
	Name: null,

	/**
	 * Namespace of the property.
	 * @api
	 * @type {string}
	 */
	NamespaceUri: null,

	/**
	 * Initializes new instance of PropertyName.
	 * @classdesc WebDAV property name.
	 * @constructs
	 * @param {string} sName Name of the property.
	 * @param {string} sNamespaceUri Namespace of the property.
	 * @throws ITHit.Exceptions.ArgumentNullException
	 */
	constructor: function(sName, sNamespaceUri) {

		// Check passed arguments type
		ITHit.WebDAV.Client.WebDavUtil.VerifyArgumentNotNullOrEmpty(sName, "sName");

		this.Name         = sName;
		this.NamespaceUri = sNamespaceUri;
	},

	/**
	 * Checks whether objects are equal.
	 * @param {ITHit.WebDAV.Client.PropertyName} oObj An object to compare with the PropertyName object.
	 * @param {boolean} bIgnoreCase Specifies if the search is case sensitive or case insensitive.
	 * @returns {boolean} True if the PropertyName and oObj are both PropertyName objects, and every component
	 * of the PropertyName object matches the corresponding component of oObj; otherwise, false.
	 */
	Equals: function(oObj, bIgnoreCase) {
		bIgnoreCase = bIgnoreCase || false;

		if (this == oObj) {
			return true;
		}

		if ( !oObj instanceof ITHit.WebDAV.Client.PropertyName ) {
			return false;
		}

		return bIgnoreCase ?
			this.Name.toLowerCase() === oObj.Name.toLowerCase() && this.NamespaceUri.toLowerCase() === oObj.NamespaceUri.toLowerCase() :
			this.Name === oObj.Name && this.NamespaceUri === oObj.NamespaceUri
	},

	/**
	 * Check whether property is standard.
	 * @returns {boolean} Whether property is standard.
	 */
	IsStandardProperty: function () {

		// Declare standard properties.
		if (!ITHit.WebDAV.Client.PropertyName.StandardNames) {
			ITHit.WebDAV.Client.PropertyName.StandardNames = [
				ITHit.WebDAV.Client.DavConstants.ResourceType,
				ITHit.WebDAV.Client.DavConstants.DisplayName,
				ITHit.WebDAV.Client.DavConstants.CreationDate,
				ITHit.WebDAV.Client.DavConstants.GetLastModified,
				ITHit.WebDAV.Client.DavConstants.GetContentLength,
				ITHit.WebDAV.Client.DavConstants.GetContentType,
				ITHit.WebDAV.Client.DavConstants.GetETag,
				ITHit.WebDAV.Client.DavConstants.IsCollection,
				ITHit.WebDAV.Client.DavConstants.IsFolder,
				ITHit.WebDAV.Client.DavConstants.IsHidden,
				ITHit.WebDAV.Client.DavConstants.SupportedLock,
				ITHit.WebDAV.Client.DavConstants.LockDiscovery,
				ITHit.WebDAV.Client.DavConstants.GetContentLanguage,
				ITHit.WebDAV.Client.DavConstants.Source,
				ITHit.WebDAV.Client.DavConstants.QuotaAvailableBytes,
				ITHit.WebDAV.Client.DavConstants.QuotaUsedBytes,
				new ITHit.WebDAV.Client.PropertyName("Win32FileAttributes", 'urn:schemas-microsoft-com:')
			];
		}

		// Search whether property is standard.
		for (var i = 0; i < ITHit.WebDAV.Client.PropertyName.StandardNames.length; i++) {
			if (this.Equals(ITHit.WebDAV.Client.PropertyName.StandardNames[i])) {
				return true;
			}
		}

		return false;
	},

	/**
	 * Check exists "DAV:" namespace
	 * @returns {boolean} Whether property is standard.
	 */
	HasDavNamespace: function () {
		return this.NamespaceUri === ITHit.WebDAV.Client.DavConstants.NamespaceUri;
	},

	/**
	 * Returns string representation of current property name.
	 * @api
	 * @returns {string} String representation of current property name.
	 */
	toString: function() {
		return this.NamespaceUri + ':' + this.Name;
	}

});



;
(function () {

	var sNamespaceUri = 'DAV:';

	/**
	 * WebDAV properties and constants enumeration
	 * @enum {ITHit.WebDAV.Client.PropertyName}
	 * @class ITHit.WebDAV.Client.DavConstants
	 */
	ITHit.DefineClass('ITHit.WebDAV.Client.DavConstants', null, {
		__static: /** @lends ITHit.WebDAV.Client.DavConstants */{

			/**
			 * WebDAV default namespace uri
			 * @readonly
			 * @type {string}
			 */
			NamespaceUri: sNamespaceUri,

			/**
			 * WebDAV property `comment`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			Comment: new ITHit.WebDAV.Client.PropertyName("comment", sNamespaceUri),

			/**
			 * WebDAV property `creationdate`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			CreationDate: new ITHit.WebDAV.Client.PropertyName("creationdate", sNamespaceUri),

			/**
			 * WebDAV property `creator-displayname`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			CreatorDisplayName: new ITHit.WebDAV.Client.PropertyName("creator-displayname", sNamespaceUri),

			/**
			 * WebDAV property `displayname`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			DisplayName: new ITHit.WebDAV.Client.PropertyName("displayname", sNamespaceUri),

			/**
			 * WebDAV property `getcontentlength`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			GetContentLength: new ITHit.WebDAV.Client.PropertyName("getcontentlength", sNamespaceUri),

			/**
			 * WebDAV property `getcontenttype`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			GetContentType: new ITHit.WebDAV.Client.PropertyName("getcontenttype", sNamespaceUri),

			/**
			 * WebDAV property `getetag`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			GetETag: new ITHit.WebDAV.Client.PropertyName("getetag", sNamespaceUri),

			/**
			 * WebDAV property `getlastmodified`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			GetLastModified: new ITHit.WebDAV.Client.PropertyName("getlastmodified", sNamespaceUri),

			/**
			 * WebDAV property `iscollection`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			IsCollection: new ITHit.WebDAV.Client.PropertyName("iscollection", sNamespaceUri),

			/**
			 * WebDAV property `isFolder`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			IsFolder: new ITHit.WebDAV.Client.PropertyName("isFolder", sNamespaceUri),

			/**
			 * WebDAV property `ishidden`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			IsHidden: new ITHit.WebDAV.Client.PropertyName("ishidden", sNamespaceUri),

			/**
			 * WebDAV property `resourcetype`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			ResourceType: new ITHit.WebDAV.Client.PropertyName("resourcetype", sNamespaceUri),

			/**
			 * WebDAV property `supportedlock`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			SupportedLock: new ITHit.WebDAV.Client.PropertyName("supportedlock", sNamespaceUri),

			/**
			 * WebDAV property `lockdiscovery`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			LockDiscovery: new ITHit.WebDAV.Client.PropertyName("lockdiscovery", sNamespaceUri),

			/**
			 * WebDAV property `getcontentlanguage`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			GetContentLanguage: new ITHit.WebDAV.Client.PropertyName("getcontentlanguage", sNamespaceUri),

			/**
			 * WebDAV property `source`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			Source: new ITHit.WebDAV.Client.PropertyName("source", sNamespaceUri),

			/**
			 * WebDAV property `quota-available-bytes`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			QuotaAvailableBytes: new ITHit.WebDAV.Client.PropertyName("quota-available-bytes", sNamespaceUri),

			/**
			 * WebDAV property `quota-used-bytes`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			QuotaUsedBytes: new ITHit.WebDAV.Client.PropertyName("quota-used-bytes", sNamespaceUri),

			/**
			 * WebDAV property `version-name`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			VersionName: new ITHit.WebDAV.Client.PropertyName("version-name", sNamespaceUri),

			/**
			 * WebDAV property `version-history`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			VersionHistory: new ITHit.WebDAV.Client.PropertyName("version-history", sNamespaceUri),

			/**
			 * WebDAV property `checked-in`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			CheckedIn: new ITHit.WebDAV.Client.PropertyName("checked-in", sNamespaceUri),

			/**
			 * WebDAV property `checked-out`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			CheckedOut: new ITHit.WebDAV.Client.PropertyName("checked-out", sNamespaceUri),

			/**
			 * WebDAV constant `src`
			 * @readonly
			 * @type {string}
			 */
			Src: 'src',

			/**
			 * WebDAV constant `dst`
			 * @readonly
			 * @type {string}
			 */
			Dst: 'dst',

			/**
			 * WebDAV constant `link`
			 * @readonly
			 * @type {string}
			 */
			Link: 'link',

			/**
			 * WebDAV slash constant
			 * @readonly
			 * @type {string}
			 */
			Slash: '/',

			/**
			 * WebDAV depndency failed error code
			 * @readonly
			 * @type {number}
			 */
			DepndencyFailedCode: 424,

			/**
			 * WebDAV locked error code
			 * @readonly
			 * @type {number}
			 */
			LockedCode: 423,

			/**
			 * WebDAV opaque lock token constant
			 * @readonly
			 * @type {string}
			 */
			OpaqueLockToken: 'opaquelocktoken:',

			/**
			 * WebDAV error property `quota-not-exceeded`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			QuotaNotExceeded: new ITHit.WebDAV.Client.PropertyName("quota-not-exceeded", sNamespaceUri),

			/**
			 * WebDAV error property `sufficient-disk-space`
			 * @readonly
			 * @type {ITHit.WebDAV.Client.PropertyName}
			 */
			SufficientDiskSpace: new ITHit.WebDAV.Client.PropertyName("sufficient-disk-space", sNamespaceUri),

			/**
			 * WebDAV protocol name
			 * @readonly
			 * @type {string}
			 */
			ProtocolName: "dav10"
		}
	});

})();


ITHit.oNS = ITHit.Declare('ITHit.Exceptions');

/*
 * Wrong argument value.
 * @class ITHit.Exceptions.ArgumentException
 * @extends ITHit.Exception
 */
/*
 * Initializes a new instance of the ArgumentException class with a specified error message and variable name wrong value of which is caused an exception.
 * @constructor ArgumentException
 * 
 * @param {String} sMessage  The error message that explains the reason for the exception.
 * @param {String} sVariable The name of the parameter that caused the current exception.
 */
ITHit.oNS.ArgumentException = function(sMessage, sVariable) {
	
	sMessage += ' Variable name: "'+ sVariable +'"';
	
	// Inheritance definition.
	ITHit.Exceptions.ArgumentException.baseConstructor.call(this, sMessage);
}

// Extend class.
ITHit.Extend(ITHit.oNS.ArgumentException, ITHit.Exception);

// Exception name.
ITHit.oNS.ArgumentException.prototype.Name = 'ArgumentException';

;
(function () {

	/**
	 * @class ITHit.WebDAV.Client.Depth
	 */
	var self = ITHit.DefineClass('ITHit.WebDAV.Client.Depth', null, /** @lends ITHit.WebDAV.Client.Depth.prototype */{

		__static: /** @lends ITHit.WebDAV.Client.Depth */{

			/**
			 * @type {ITHit.WebDAV.Client.Depth}
			 */
			Zero: null,

			/**
			 * @type {ITHit.WebDAV.Client.Depth}
			 */
			One: null,

			/**
			 * @type {ITHit.WebDAV.Client.Depth}
			 */
			Infinity: null,

			Parse: function (sValue) {

				// Switch depth variant.
				switch (sValue.toLowerCase()) {

					// Depth 0.
					case '0':
						return ITHit.WebDAV.Client.Depth.Zero;
						break;

					// Get one level.
					case '1':
						return ITHit.WebDAV.Client.Depth.One;
						break;

					// Get all.
					case 'infinity':
						return ITHit.WebDAV.Client.Depth.Infinity;
						break;

					default:
						throw new ITHit.Exceptions.ArgumentException(ITHit.Phrases.Exceptions.InvalidDepthValue, 'sValue');

				}

			}
		},

		/**
		 *
		 * @param {string|number} mValue
		 */
		constructor: function (mValue) {
			this.Value = mValue;
		}

	});

	self.Zero = new self(0);
	self.One = new self(1);
	self.Infinity = new self('Infinity');

})();
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.HttpMethod', null, /** @lends ITHit.WebDAV.Client.Methods.HttpMethod.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.HttpMethod */{

		/**
		 * @param {ITHit.WebDAV.Client.Request} oRequest
		 * @param {string} sHref
		 * @param {...*} otherParam
		 * @returns {ITHit.WebDAV.Client.WebDavRequest}
		 */
		Go: function (oRequest, sHref, otherParam) {
			// Create request.
			var oWebDavRequest = this._CreateRequest.apply(this, arguments);
			var oResponse = oWebDavRequest.GetResponse();

			return this._ProcessResponse(oResponse, sHref);
		},

		/**
		 * @param {ITHit.WebDAV.Client.Request} oRequest
		 * @param {string} sHref
		 * @param {...*} otherParam
		 * @returns {ITHit.WebDAV.Client.WebDavRequest}
		 */
		GoAsync: function (oRequest, sHref, otherParam) {
			// Create request.
			var fCallback = arguments[arguments.length - 1];
			var oWebDavRequest = this._CreateRequest.apply(this, arguments);

			var that = this;
			oWebDavRequest.GetResponse(function (oAsyncResult) {
				if (oAsyncResult.IsSuccess) {
					oAsyncResult.Result = that._ProcessResponse(oAsyncResult.Result, sHref);
				}
				fCallback(oAsyncResult);
			});

			return oWebDavRequest;
		},

		/**
		 *
		 * @protected
		 * @returns {ITHit.WebDAV.Client.WebDavRequest}
		 */
		_CreateRequest: function () {
			// @todo throw not implement
		},

		_ProcessResponse: function (oResponse, sHref) {
			return new this(oResponse, sHref);
		}

	},

	/**
	 * @type {ITHit.WebDAV.Client.WebDavResponse}
	 */
	Response: null,

	/**
	 * @type {string}
	 */
	Href: null,

	/**
	 * Base class for all Http methods. Provides logging functionality.
	 * @constructs
	 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
	 * @param {string} sHref
	 */
	constructor: function (oResponse, sHref) {
		this.Response = oResponse;
		this.Href = sHref;

		this._Init();
	},

	_Init: function () {
	}
});


;
(function() {

	/**
	 * Structure that describes HTTP response's status.
	 * @api
	 * @class ITHit.WebDAV.Client.HttpStatus
	 */
	ITHit.DefineClass('ITHit.WebDAV.Client.HttpStatus', null, /** @lends ITHit.WebDAV.Client.HttpStatus.prototype */{

		__static: /** @lends ITHit.WebDAV.Client.HttpStatus */{

			/**
			 * No status defined.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			None: null,

			/**
			 * The request requires user authentication.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			Unauthorized: null,

			/**
			 * The request has succeeded.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			OK: null,

			/**
			 * The request has been fulfilled and resulted in a new resource being created.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			Created: null,

			/**
			 * The server has fulfilled the request but does not need to return an entity-body, and might want to
			 * return updated meta information.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			NoContent: null,

			/**
			 * The server has fulfilled the partial GET request for the resource.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			PartialContent: null,

			/**
			 * This status code provides status for multiple independent operations.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			MultiStatus: null,

			/**
			 * This status code is used instead if 302 redirect. This is because 302 code is processed automatically
			 * and there is no way to process redirect to login page.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			Redirect: null,

			/**
			 * The request could not be understood by the server due to malformed syntax. The client SHOULD NOT repeat
			 * the request without modifications.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			BadRequest: null,

			/**
			 * The server has not found anything matching the Request-URI.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			NotFound: null,

			/**
			 * The method specified in the Request-Line is not allowed for the resource identified by the Request-URI.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			MethodNotAllowed: null,

			/**
			 * The precondition given in one or more of the request-header fields evaluated to false when it was tested
			 * on the server.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			PreconditionFailed: null,

			/**
			 * The source or destination resource of a method is locked.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			Locked: null,

			/**
			 * The method could not be performed on the resource because the requested action depended on another
			 * action and that action failed.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			DependencyFailed: null,

			/**
			 * The server understood the request, but is refusing to fulfill it.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			Forbidden: null,

			/**
			 * The request could not be completed due to a conflict with the current state of the resource.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			Conflict: null,

			/**
			 * The server does not support the functionality required to fulfill the request.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			NotImplemented: null,

			/**
			 * The server, while acting as a gateway or proxy, received an invalid response from the upstream
			 * server it accessed in attempting to fulfill the request.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			BadGateway: null,

			/**
			 * The method could not be performed on the resource because the server is unable to store the
			 * representation needed to successfully complete the request.
			 * @api
			 * @type {ITHit.WebDAV.Client.HttpStatus}
			 */
			InsufficientStorage: null,

			/**
			 * Parses HttpStatus structure from string containing status information.
			 * @api
			 * @param {string} sStatus String containing status information.
			 * @returns {ITHit.WebDAV.Client.HttpStatus} HttpStatus structure that describes current status.
			 */
			Parse: function(sStatus) {
				var aParts  = sStatus.split(' ');
				var iStatus = parseInt(aParts[1]);

				aParts.splice(0, 2);

				return new ITHit.WebDAV.Client.HttpStatus(iStatus, aParts.join(' '));
			}

		},

		/**
		 * @type {number}
		 */
		Code: null,

		/**
		 * @type {string}
		 */
		Description: null,

		/**
		 * Represents response status.
		 * Initializes a new instance of t,he HttpStatus structure with code and description specified.
		 * @param {number} iCode Code of the status.
		 * @param {string} sDescription Description of the status.
		 */
		constructor: function(iCode, sDescription) {
			this.Code = iCode;
			this.Description = sDescription;
		},

		/**
		 * Indicates whether the current HttpStatus structure is equal to another HttpStatus structure.
		 * @api
		 * @param {ITHit.WebDAV.Client.HttpStatus} oHttpStatus HttpStatus object to compare.
		 * @returns {boolean} True if the current object is equal to the other parameter; otherwise, false.
		 */
		Equals: function(oHttpStatus) {
			if ( !oHttpStatus || !(oHttpStatus instanceof ITHit.WebDAV.Client.HttpStatus) ) {
				return false;
			}

			return this.Code === oHttpStatus.Code;
		},

		/**
		 * Returns true if status is successful for Create operation.
		 * @api
		 * @returns {boolean} Returns true if status is successful for Create operation.
		 */
		IsCreateOk: function() {
			return this.Equals(ITHit.WebDAV.Client.HttpStatus.Created);
		},

		/**
		 * Returns true if status is successful for Delete operation.
		 * @api
		 * @returns {boolean} Returns true if status is successful for Delete operation.
		 */
		IsDeleteOk: function() {
			return this.Equals(ITHit.WebDAV.Client.HttpStatus.OK) || this.Equals(ITHit.WebDAV.Client.HttpStatus.NoContent);
		},

		/**
		 * Returns true if status is successful.
		 * @api
		 * @returns {boolean} Returns true if status is successful.
		 */
		IsOk: function() {
			return this.Equals(ITHit.WebDAV.Client.HttpStatus.OK);
		},

		/**
		 * Returns true if status is successful for Copy or Move operation.
		 * @api
		 * @returns {boolean} Returns true if status is successful for Copy or Move operation.
		 */
		IsCopyMoveOk: function() {
			return this.Equals(ITHit.WebDAV.Client.HttpStatus.NoContent) || this.Equals(ITHit.WebDAV.Client.HttpStatus.Created);
		},

		/**
		 * Returns true if status is successful for Get operation.
		 * @api
		 * @returns {boolean} Returns true if status is successful for Get operation.
		 */
		IsGetOk: function() {
			return this.Equals(ITHit.WebDAV.Client.HttpStatus.OK) || this.Equals(ITHit.WebDAV.Client.HttpStatus.PartialContent);
		},

		/**
		 * Returns true if status is successful for Put operation.
		 * @api
		 * @returns {boolean} Returns true if status is successful for Put operation.
		 */
		IsPutOk: function() {
			return this.Equals(ITHit.WebDAV.Client.HttpStatus.OK) || this.Equals(ITHit.WebDAV.Client.HttpStatus.Created) || this.Equals(ITHit.WebDAV.Client.HttpStatus.NoContent);
		},

		/**
		 * Returns true if status is successful for Unlock operation.
		 * @api
		 * @returns {boolean} Returns true if status is successful for Unlock operation.
		 */
		IsUnlockOk: function() {
			return this.Equals(ITHit.WebDAV.Client.HttpStatus.OK) || this.Equals(ITHit.WebDAV.Client.HttpStatus.NoContent);
		},

		/**
		 * Returns true if status is successful for Head operation.
		 * @api
		 * @returns {boolean} Returns true if status is successful for Head operation.
		 */
		IsHeadOk: function() {
			return this.Equals(ITHit.WebDAV.Client.HttpStatus.OK) || this.Equals(ITHit.WebDAV.Client.HttpStatus.NotFound);
		},


		/**
		 * Returns true if status is successful for Proppatch operation.
		 * @api
		 * @returns {boolean} Returns true if status is successful for Proppatch operation.
		 */
		IsUpdateOk: function() {
			return this.Equals(ITHit.WebDAV.Client.HttpStatus.OK) || this.Equals(ITHit.WebDAV.Client.HttpStatus.None);
		},

		/**
		 * Returns true if status is successful.
		 * @api
		 * @returns {boolean} Returns true if status is successful.
		 */
		IsSuccess: function() {
			return (parseInt(this.Code / 100) == 2);
		}

	});

})();

ITHit.WebDAV.Client.HttpStatus.None =                new ITHit.WebDAV.Client.HttpStatus(0, '');
ITHit.WebDAV.Client.HttpStatus.Unauthorized =        new ITHit.WebDAV.Client.HttpStatus(401, 'Unauthorized');
ITHit.WebDAV.Client.HttpStatus.OK =                  new ITHit.WebDAV.Client.HttpStatus(200, 'OK');
ITHit.WebDAV.Client.HttpStatus.Created =             new ITHit.WebDAV.Client.HttpStatus(201, 'Created');
ITHit.WebDAV.Client.HttpStatus.NoContent =           new ITHit.WebDAV.Client.HttpStatus(204, 'No Content');
ITHit.WebDAV.Client.HttpStatus.PartialContent =      new ITHit.WebDAV.Client.HttpStatus(206, 'Partial Content');
ITHit.WebDAV.Client.HttpStatus.MultiStatus =         new ITHit.WebDAV.Client.HttpStatus(207, 'Multi-Status');
ITHit.WebDAV.Client.HttpStatus.Redirect =            new ITHit.WebDAV.Client.HttpStatus(278, 'Redirect');
ITHit.WebDAV.Client.HttpStatus.BadRequest =          new ITHit.WebDAV.Client.HttpStatus(400, 'Bad Request');
ITHit.WebDAV.Client.HttpStatus.NotFound =            new ITHit.WebDAV.Client.HttpStatus(404, 'Not Found');
ITHit.WebDAV.Client.HttpStatus.MethodNotAllowed =    new ITHit.WebDAV.Client.HttpStatus(405, 'Method Not Allowed');
ITHit.WebDAV.Client.HttpStatus.PreconditionFailed =  new ITHit.WebDAV.Client.HttpStatus(412, 'Precondition Failed');
ITHit.WebDAV.Client.HttpStatus.Locked =              new ITHit.WebDAV.Client.HttpStatus(423, 'Locked');
ITHit.WebDAV.Client.HttpStatus.DependencyFailed =    new ITHit.WebDAV.Client.HttpStatus(424, 'Dependency Failed');
ITHit.WebDAV.Client.HttpStatus.Forbidden =           new ITHit.WebDAV.Client.HttpStatus(403, 'Forbidden');
ITHit.WebDAV.Client.HttpStatus.Conflict =            new ITHit.WebDAV.Client.HttpStatus(409, 'Conflict');
ITHit.WebDAV.Client.HttpStatus.NotImplemented =      new ITHit.WebDAV.Client.HttpStatus(501, 'Not Implemented');
ITHit.WebDAV.Client.HttpStatus.BadGateway =          new ITHit.WebDAV.Client.HttpStatus(502, 'Bad gateway');
ITHit.WebDAV.Client.HttpStatus.InsufficientStorage = new ITHit.WebDAV.Client.HttpStatus(507, 'Insufficient Storage');


ITHit.DefineClass('ITHit.WebDAV.Client.Property', null, /** @lends ITHit.WebDAV.Client.Property.prototype */{

	/**
	 * Property Name.
	 * @api
	 * @type {string|ITHit.WebDAV.Client.PropertyName}
	 */
	Name: null,

	/**
	 * Property value.
	 * @api
	 * @type {*}
	 */
	Value: null,

	/**
	 * Initializes new string valued property.
	 * @api
	 * @classdesc Represents custom property exposed by WebDAV hierarchy items.
	 * @constructs
	 * @param {string|ITHit.WebDAV.Client.PropertyName} sName Name of the property.
	 * @param {string} [sValue] Property value.
	 * @param {string} [sNamespace] Namespace of the property.
	 * @throws ITHit.Exception
	 */
	constructor: function(sName, sValue, sNamespace) {
		switch (arguments.length) {

			case 1:
				// Declare variable.
				var oElement = sName;

				// Check variable.
				ITHit.WebDAV.Client.WebDavUtil.VerifyArgumentNotNull(oElement, 'oElement');

				this.Name    = new ITHit.WebDAV.Client.PropertyName(oElement.localName(), oElement.namespaceURI());
				this.Value   = oElement;

				break;

			case 2:
				// Declare variables.
				var oName        = sName,
					sStringValue = sValue;

				// Check variables.
				ITHit.WebDAV.Client.WebDavUtil.VerifyArgumentNotNull(oName, 'oName');
				ITHit.WebDAV.Client.WebDavUtil.VerifyArgumentNotNull(sStringValue, 'sStringValue');

				this.Name   = oName;

				// Create element.
				var oXmlDoc = new ITHit.XMLDoc(),
					oElem   = oXmlDoc.createElementNS(oName.NamespaceUri, oName.Name);
				oElem.appendChild(oXmlDoc.createTextNode(sStringValue));
				this.Value  = oElem;

				break;

			case 3:
				// Declare variables.
				var sName      = sName,
					sValue     = sValue,
					sNameSpace = sNamespace;

				// Check variables.
				ITHit.WebDAV.Client.WebDavUtil.VerifyArgumentNotNullOrEmpty(sName, "sName");
				ITHit.WebDAV.Client.WebDavUtil.VerifyArgumentNotNull(sValue, "sValue");
				ITHit.WebDAV.Client.WebDavUtil.VerifyArgumentNotNullOrEmpty(sNameSpace, "sNameSpace");

				this.Name   = new ITHit.WebDAV.Client.PropertyName(sName, sNameSpace);

				// Create element.
				var oXmlDoc = new ITHit.XMLDoc(),
					oElem   = oXmlDoc.createElementNS(sNameSpace, sName);
				oElem.appendChild(oXmlDoc.createTextNode(sValue));
				this.Value  = oElem;

				break;

			default:
				throw ITHit.Exception(ITHit.Phrases.Exceptions.WrongCountPropertyInputParameters.Paste(arguments.length));
		}
	},

	/**
	 * String value of the custom property.
	 * @api
	 * @returns {string} String value of the custom property.
	 */
	StringValue: function() {
		return this.Value.firstChild().nodeValue();
	},

	/**
	 * Returns string representation of current property.
	 * @returns {string} String representation of PropertyName.
	 */
	toString: function() {
		return this.Name.toString();
	}

});


ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Propstat', null, /** @lends ITHit.WebDAV.Client.Methods.Propstat.prototype */{

	PropertiesByNames: null,
	Properties: null,
	ResponseDescription: '',
	Status: '',

	/**
	 * @constructs
	 * @param oElement
	 */
	constructor: function(oElement) {

		// Declare class variables.
		this.PropertiesByNames   = {};
		this.Properties          = [];

		var oNode;

		// Create namespace resolver.
		var oResolver = new ITHit.XPath.resolver();
		oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);

		// Get response description.
		if ( oNode = ITHit.XPath.selectSingleNode('d:responsedescription', oElement, oResolver) ) {
			this.ResponseDescription = oNode.firstChild().nodeValue();
		}

		// Get status.
		oNode = ITHit.XPath.selectSingleNode('d:status', oElement, oResolver);
		this.Status = ITHit.WebDAV.Client.HttpStatus.Parse(oNode.firstChild().nodeValue());

		// Get properties.
		var oRes = ITHit.XPath.evaluate('d:prop/*', oElement, oResolver);
		while ( oNode = oRes.iterateNext() ) {

			var oProperty = new ITHit.WebDAV.Client.Property(oNode.cloneNode());
			var sPropName = oProperty.Name;

			if ('undefined' == typeof this.PropertiesByNames[sPropName]) {
				this.PropertiesByNames[sPropName] = oProperty;
			} else {
				var aChildNodes = oNode.childNodes();

				for ( var i = 0; i < aChildNodes.length; i++ ) {
					this.PropertiesByNames[sPropName].Value.appendChild(aChildNodes[i]);
				}
			}
			this.Properties.push(oProperty);
		}
	}

});


ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Response', null, /** @lends ITHit.WebDAV.Client.Methods.Response.prototype */{

	Href: '',
	ResponseDescription: '',
	Status: '',
	Propstats: null,

	/**
	 * @constructs
	 * @param oResponseItem
	 * @param sOriginalUri
	 */
	constructor: function(oResponseItem, sOriginalUri) {

		// Declare class properties.
		this.Propstats = [];

		// Declare variables.
		var oNode;

		// Create namespace resolver.
		var oResolver = new ITHit.XPath.resolver();
		oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);

		// Get response href.
		this.Href = ITHit.XPath.selectSingleNode('d:href', oResponseItem, oResolver).firstChild().nodeValue();

		// Get description if specified.
		if ( oNode = ITHit.XPath.selectSingleNode('d:responsedescription', oResponseItem, oResolver) ) {
			this.ResponseDescription = oNode.firstChild().nodeValue();
		}

		// Get response status if specified.
		if ( oNode = ITHit.XPath.selectSingleNode('d:status', oResponseItem, oResolver) ) {
			this.Status = ITHit.WebDAV.Client.HttpStatus.Parse(oNode.firstChild().nodeValue());
		}

		// Get propstat.
		var oRes = ITHit.XPath.evaluate('d:propstat', oResponseItem, oResolver);
		while ( oNode = oRes.iterateNext() ) {
			this.Propstats.push(new ITHit.WebDAV.Client.Methods.Propstat(oNode.cloneNode()));
		}
	}

});


ITHit.DefineClass('ITHit.WebDAV.Client.Methods.MultiResponse', null, /** @lends ITHit.WebDAV.Client.Methods.MultiResponse.prototype */{

	ResponseDescription: '',
	Responses: null,
	TotalItems: null,

	/**
	 *
	 * @param oXmlDoc
	 * @param sOriginalUri
	 * @constructs
	 */
	constructor: function(oXmlDoc, sOriginalUri) {

		// Declare properties.
		this.ResponseDescription = '';
		this.Responses = [];

		// Create namespace resolver.
		var oResolver = new ITHit.XPath.resolver();
		oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);
	    // add ithitp namespace which is used for paging 
		oResolver.add('ithitp', "https://www.ithit.com/pagingschema/");

		var oNode;
	    // Select paging node
		var oPagingRes = ITHit.XPath.evaluate('/d:multistatus/ithitp:total', oXmlDoc, oResolver);
		if ((oNode = oPagingRes.iterateNext())) {
		    this.TotalItems = parseInt(oNode.firstChild().nodeValue());
		}

		// Select nodes.
		var oRes = ITHit.XPath.evaluate('/d:multistatus/d:response', oXmlDoc, oResolver);

		// Loop through selected nodes. 		
		while( (oNode = oRes.iterateNext())) {
			this.Responses.push(new ITHit.WebDAV.Client.Methods.Response(oNode.cloneNode(), sOriginalUri));
		}

		// Get response description if specified.
		ITHit.XPath.evaluate('/d:multistatus/d:responsedescription', oXmlDoc, oResolver, oRes);

		if ( (oNode = oRes.iterateNext()) ) {
			this.ResponseDescription = oNode.firstChild().nodeValue();
		}
	}

});


/**
 * Instance of this class is passed to callback function. It provides information about success or failure of
 * the operation as well as you will use it to get the results of the asynchronous call.
 * @api
 * @class ITHit.WebDAV.Client.AsyncResult
 */
ITHit.DefineClass('ITHit.WebDAV.Client.AsyncResult', null, /** @lends ITHit.WebDAV.Client.AsyncResult.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.AsyncResult */{
		/**
		 * Creates successful result.
		 * @param {Object} oResult
		 * @return {ITHit.WebDAV.Client.AsyncResult}
		 */
		CreateSuccessfulResult: function(oResult) {
			return new ITHit.WebDAV.Client.AsyncResult(oResult, true, null);
		},

		/**
		 * Creates failed result.
		 * @param {ITHit.WebDAV.Client.Exceptions.WebDavException|Error|null} oError
		 * @return {ITHit.WebDAV.Client.AsyncResult}
		 */
		CreateFailedResult: function(oError) {
			return new ITHit.WebDAV.Client.AsyncResult(null, false, oError);
		}
	},


	/**
	 * Result value. Can be any type, each method may put there appropriate object which before was returned directly.
	 * Null if request was unsuccessful.
	 * @api
	 * @type {*}
	 */
	Result: null,

	/**
	 * Flag of either async request result was successful or not.
	 * @api
	 * @type {boolean}
	 */
	IsSuccess: null,

	/**
	 * Error (Exception) object. Describes the type of error that occurred. Null if request was successful.
	 * @api
	 * @type {ITHit.WebDAV.Client.Exceptions.WebDavException|Error|null}
	 */
	Error: null,

    /**
     * Status of HTTP response retrieved either from Result or Error objects
     * @api
     * @type {ITHit.WebDAV.Client.HttpStatus}
     */
    Status: null,

	/**
	 *
	 * @param {*} oResult
	 * @param {boolean} bSuccess
	 * @param {ITHit.WebDAV.Client.Exceptions.WebDavException|Error|null} oError
	 */
	constructor: function(oResult, bSuccess, oError) {
		this.Result = oResult;
		this.IsSuccess = bSuccess;
		this.Error = oError;
		if (this.Error !== null) {
		    this.Status = this.Error.Status;
		} else if (this.Result !== null) {
		    this.Status = this.Result.Status;
		}
	}

});


ITHit.DefineClass('ITHit.WebDAV.Client.OrderProperty', null, /** @lends ITHit.WebDAV.Client.OrderProperty.prototype */{
	/**
	 * Property name.
	 * @api
	 * @type {ITHit.WebDAV.Client.PropertyName}
	 */
    Property: null,

	/**
	 * Order direction.
	 * @api
	 * @type {boolean}
	 */
    Ascending: true,

	/**
	 * Initializes new instance of OrderProperty.
     * @api
	 * @classdesc WebDAV order Property.
	 * @constructs
	 * @param {ITHit.WebDAV.Client.PropertyName} sProperty Property name.
	 * @param {boolean} sAscending Order direction.
	 */
    constructor: function (sProperty, sAscending) {

        this.Property = sProperty;
        this.Ascending = sAscending;
    },

	/**
	 * Returns string representation of current property name.
	 * @api
	 * @returns {string} String representation of current property name.
	 */
    toString: function () {
        return this.Property.toString() + '; Sorting:' + (this.Ascending ? 'Ascending' : 'Descending');
    }

});



/**
 * Method to perform Propfind request to a server.
 * Create new instance of Propfind class.
 * @class ITHit.WebDAV.Client.Methods.Propfind
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Propfind', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Propfind.prototype */{

    __static: /** @lends ITHit.WebDAV.Client.Methods.Propfind */{

        /**
		 * Propfind modes.
		 */
        PropfindMode: {
            SelectedProperties: 'SelectedProperties',
            PropertyNames: 'PropertyNames'
        },

        Go: function (oRequest, sUri, iMode, aProperties, oDepth, sHost) {
            return this.GoAsync(oRequest, sUri, iMode, aProperties, oDepth, sHost);
        },

        GoAsync: function (oRequest, sUri, iMode, aProperties, oDepth, sHost, fCallback, offset, nResults, aOrderProperties) {

            // Create request object.
            var oWebDavRequest = ITHit.WebDAV.Client.Methods.Propfind.createRequest(oRequest, sUri, iMode, aProperties, oDepth, sHost, offset, nResults, aOrderProperties);

            var self = this;
            var fOnResponse = typeof fCallback === 'function'
                ? function (oResult) {
                    self._GoCallback(oRequest, sUri, oResult, fCallback)
                }
                : null;

            // Make request.
            var oResponse = oWebDavRequest.GetResponse(fOnResponse);

            if (typeof fCallback !== 'function') {
                var oResult = new ITHit.WebDAV.Client.AsyncResult(oResponse, oResponse != null, null);
                return this._GoCallback(oRequest, sUri, oResult, fCallback);
            } else {
                return oWebDavRequest;
            }
        },

        _GoCallback: function (oRequest, sUri, oResult, fCallback) {

            var oResponse = oResult;
            var bSuccess = true;
            var oError = null;
            var oStatus = null; /** @typedef {ITHit.WebDAV.Client.HttpStatus} */

            if (oResult instanceof ITHit.WebDAV.Client.AsyncResult) {
                oResponse = oResult.Result;
                bSuccess = oResult.IsSuccess;
                oError = oResult.Error;
            }
            if (oResponse !== null) {
                oStatus = oResponse.Status;
            }

            var oPropfind = null;
            if (bSuccess) {
                // Receive data.
                var oResponseData = oResponse.GetResponseStream();

                var oMultiResponse = new ITHit.WebDAV.Client.Methods.MultiResponse(oResponseData, sUri);
                oPropfind = new ITHit.WebDAV.Client.Methods.Propfind(oMultiResponse);
            }
            // Return response.
            if (typeof fCallback === 'function') {
                if (oStatus !== null) {
                    oPropfind.Status = oStatus;
                }
                var oPropfindResult = new ITHit.WebDAV.Client.AsyncResult(oPropfind, bSuccess, oError);
                fCallback.call(this, oPropfindResult);
            } else {
                return oPropfind;
            }
        },

        createRequest: function (oRequest, sUri, iMode, aProperties, oDepth, sHost, offset, nResults, aOrderProperties) {

            // Create request object.
            var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sUri);

            // Set method.
            oWebDavRequest.Method('PROPFIND');

            // Add headers.
            oWebDavRequest.Headers.Add('Depth', oDepth.Value);
            oWebDavRequest.Headers.Add('Content-Type', 'text/xml; charset="utf-8"');

            // Create XML document.
            var oWriter = new ITHit.XMLDoc();

            // Create root element.
            var propfind = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'propfind');

            // Switch property mode.
            switch (iMode) {

                // Namespace mode.
                case ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties:

                    // All properties.
                    if (!aProperties || !aProperties.length) {
                        var propEl = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'allprop');

                        // Selected properties.
                    } else {
                        var propEl = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'prop');
                        for (var i = 0; i < aProperties.length; i++) {
                            var prop = oWriter.createElementNS(aProperties[i].NamespaceUri, aProperties[i].Name);
                            propEl.appendChild(prop);
                        }
                    }
                    break;

                    // Property mode.
                case ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.PropertyNames:
                    var propEl = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'propname');
                    break;
            }

            // Append created child nodes.
            propfind.appendChild(propEl);

            // add limit child nodes
            if (offset !== undefined && offset != null && nResults !== undefined && nResults != null) {
                var limit = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'limit');
                var eOffset = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'offset');
                var eNResults = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'nresults');

                eOffset.appendChild(oWriter.createTextNode(offset));
                eNResults.appendChild(oWriter.createTextNode(nResults));
                limit.appendChild(eNResults);
                limit.appendChild(eOffset);
                propfind.appendChild(limit);
            }

            // add order properties child nodes.
            if (aOrderProperties && aOrderProperties.length) {
                var orderbyEl = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'orderby');
                for (var i = 0; i < aOrderProperties.length; i++) {
                    var orderEl = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'order');
                    var propEl = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'prop');
                    var propNameEl = oWriter.createElementNS(aOrderProperties[i].Property.NamespaceUri, aOrderProperties[i].Property.Name);
                    var ordEl = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, aOrderProperties[i].Ascending ? 'ascending' : 'descending');

                    propEl.appendChild(propNameEl);
                    orderEl.appendChild(propEl);
                    orderEl.appendChild(ordEl);
                    orderbyEl.appendChild(orderEl);
                }

                propfind.appendChild(orderbyEl);
            }

            oWriter.appendChild(propfind);

            // Assign created document as body for request.
            oWebDavRequest.Body(oWriter);

            return oWebDavRequest;
        }

    }
});


ITHit.DefineClass('ITHit.WebDAV.Client.Methods.SingleResponse', null, /** @lends ITHit.WebDAV.Client.Methods.SingleResponse.prototype */{

	Status: null,
	ResponseDescription: null,

	/**
	 * Contains information about server's simple response with no XML content.
	 * Create new instance of SingleResponse class.
	 * @constructs
	 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
	 */
	constructor: function(oResponse) {

		this.Status              = oResponse.Status;
		this.ResponseDescription = oResponse.Status.Description;
	}

});


/**
 * Factory class for different inheritors.
 * @class ITHit.WebDAV.Client.Methods.ResponseFactory
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.ResponseFactory', null, /** @lends ITHit.WebDAV.Client.Methods.ResponseFactory.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.ResponseFactory */{

		/**
		 * Returns suitable object of IResponse's inheritor: SingleResponse or MultiResponse.
		 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
		 * @param {string} sOriginalUri Request URI.
		 * @returns {object} SingleResponse or MultiResponse object corresponding to request.
		 */
		GetResponse: function (oResponse, sOriginalUri) {

			// Get response body.
			var oResponseData = oResponse.GetResponseStream(oResponse);

			// Check whether there is single or multi-response.
			if (!oResponseData || !oResponse.Status.Equals(ITHit.WebDAV.Client.HttpStatus.MultiStatus)) {

				// Single response.
				return new ITHit.WebDAV.Client.Methods.SingleResponse(oResponse);
			} else {

				// Multi-response.
				return new ITHit.WebDAV.Client.Methods.MultiResponse(oResponseData, sOriginalUri);
			}
		}

	}
});


/**
 * @class ITHit.WebDAV.Client.Methods.VersionControl
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.VersionControl', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.VersionControl.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.VersionControl */{

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param oLockTokens
		 * @param sHost
		 * @returns {*}
		 */
		Go: function (oRequest, sHref, oLockTokens, sHost) {
			return this._super.apply(this, arguments);
		},

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param oLockTokens
		 * @param sHost
		 * @param fCallback
		 * @returns {*}
		 */
		GoAsync: function (oRequest, sHref, oLockTokens, sHost, fCallback) {
			return this._super.apply(this, arguments);
		},

		_CreateRequest: function (oRequest, sHref, oLockTokens, sHost) {

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref, oLockTokens);

			// Set method.
			oWebDavRequest.Method('VERSION-CONTROL');

			// Return request object.
			return oWebDavRequest;
		},

		_ProcessResponse: function (oResponse, sHref) {
			// Get appropriate response object.
			var oResp = ITHit.WebDAV.Client.Methods.ResponseFactory.GetResponse(oResponse, sHref);

			return this._super(oResp);
		}

	}
});

/**
 * Enumeration of the item (Resource or Folder).
 * @api
 * @enum {string}
 * @class ITHit.WebDAV.Client.ResourceType
 */
ITHit.DefineClass('ITHit.WebDAV.Client.ResourceType', null, {
	__static: /** @lends ITHit.WebDAV.Client.ResourceType */{

		/**
		 * Item is folder.
		 * @api
		 * @readonly
		 * @type {string}
		 */
		Folder: 'Folder',

		/**
		 * Item is file.
		 * @api
		 * @readonly
		 * @type {string}
		 */
		File: 'Resource',

		Resource: 'Resource'

	}
});

/**
 * List of WebDAV properties.
 * @api
 * @class ITHit.WebDAV.Client.PropertyList
 * @extends Array
 */
ITHit.DefineClass('ITHit.WebDAV.Client.PropertyList', Array, /** @lends ITHit.WebDAV.Client.PropertyList.prototype */{

    constructor: function() {
        // Empty constructor for don't call Array.constructor
    },

    /**
     * Returns true if the with the specified property name and namespace exists in property list.
     * Returns false if does not exist.
     * @api
     * @param {ITHit.WebDAV.Client.PropertyName} oPropName Property name to search for.
     * @param {boolean} [bIgnoreCase] Specifies if the search is case sensitive or case insensitive.
     * @returns {boolean}
     */
    Has: function(oPropName, bIgnoreCase) {
        for (var i = 0, l = this.length; i < l; i++) {
            if (oPropName.Equals(this[i].Name, bIgnoreCase)) {
                return true;
            }
        }
        return false;
    },

    /**
     * Gets property value found by property name and namespace. Returns null if property with such name does not exist.
     * @api
     * @param {ITHit.WebDAV.Client.PropertyName} oPropName Property name to search for.
     * @param {boolean} [bIgnoreCase] Specifies if the search is case sensitive or case insensitive.
     * @returns {(string|null)} String representing property value or null if property with such name does not exist.
     */
    Find: function(oPropName, bIgnoreCase) {
        for (var i = 0, l = this.length; i < l; i++) {
            if (oPropName.Equals(this[i].Name, bIgnoreCase)) {
                return this[i].Value.firstChild().nodeValue();
            }
        }

        return null;
    }

});

/**
 * Base exception for all exceptions thrown by WebDAV client library.
 * Initializes a new instance of the WebDavException class with a specified error message.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.WebDavException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.WebDavException', ITHit.Exception, /** @lends ITHit.WebDAV.Client.Exceptions.WebDavException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'WebDavException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, oInnerException) {
		this._super(sMessage, oInnerException);
	}

});


/**
 * Represents information about errors occurred in different elements.
 * @api
 * @class ITHit.WebDAV.Client.Multistatus
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Multistatus', null, /** @lends ITHit.WebDAV.Client.Multistatus.prototype */{

    /**
     * Gets the generic description, if available.
     * @api
     * @type {string}
     */
    Description: null,

    /**
     * Array of the errors returned by server.
     * @api
     * @type {ITHit.WebDAV.Client.MultistatusResponse[]}
     */
    Responses: null

});

/**
 * Represents error occurred in one element.
 * @api
 * @class ITHit.WebDAV.Client.MultistatusResponse
 */
ITHit.DefineClass('ITHit.WebDAV.Client.MultistatusResponse', null, /** @lends ITHit.WebDAV.Client.MultistatusResponse.prototype */{

    /**
     * Request href
     * @api
     * @type {string}
     */
    Href: null,

    /**
     * Array of the errors returned by server.
     * @api
     * @type {string}
     */
    Description: null,

    /**
     * HTTP Status of the operation.
     * @api
     * @type {ITHit.WebDAV.Client.HttpStatus}
     */
    Status: null

});

ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.Info.MultistatusResponse', ITHit.WebDAV.Client.MultistatusResponse, /** @lends ITHit.WebDAV.Client.Exceptions.Info.MultistatusResponse.prototype */{

	/**
	 * Url of the item.
	 * @type {ITHit.WebDAV.Client.MultistatusResponse.Href}
	 */
	Href: null,

	/**
	 * Description of error, if available.
	 * @type {ITHit.WebDAV.Client.MultistatusResponse.Description}
	 */
	Description: null,

	/**
	 * HTTP Status of the operation.
	 * @type {ITHit.WebDAV.Client.MultistatusResponse.Status}
	 */
	Status: null,

	/**
	 * Represents error occurred in one element.
	 * @constructs
	 * @extends ITHit.WebDAV.Client.MultistatusResponse
	 */
	constructor: function(oResponse) {

		// Define object properties.
		this.Href = oResponse.Href;
		this.Description = oResponse.ResponseDescription;
		this.Status = oResponse.Status;

		// Loop through response propstats, look for first not OK status.
		for ( var i = 0; i < oResponse.Propstats.length; i++ ) {
			if (oResponse.Propstats[i] != ITHit.WebDAV.Client.HttpStatus.OK) {
				this.Status = oResponse.Propstats[i];
				break;
			}
		}
	}

});


ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.Info.Multistatus', ITHit.WebDAV.Client.Multistatus, /** @lends ITHit.WebDAV.Client.Exceptions.Info.Multistatus.prototype */{

	/**
	 * Gets the generic description, if available. 11
	 * @type {string}
	 */
	Description: '',

	/**
	 * Array of the errors returned by server.
	 * @type {ITHit.WebDAV.Client.MultistatusResponse[]}
	 */
	Responses: null,

	/**
	 * Represents information about errors occurred in different elements.
	 * @constructs
	 * @extends ITHit.WebDAV.Client.Multistatus
	 */
	constructor: function(oMultiResponse) {
		this.Responses = [];

		// Whether multistatus response object passed.
		if (oMultiResponse) {

			this.Description = oMultiResponse.ResponseDescription;

			// Loop through all received responses and add it to class' property.
			for ( var i = 0; i < oMultiResponse.Responses.length; i++ ) {
				this.Responses.push(new ITHit.WebDAV.Client.Exceptions.Info.MultistatusResponse(oMultiResponse.Responses[i]));
			}
		}
	}

});


/**
 * Is thrown whenever and erroneous http response is received. Initializes a new instance of the WebDavHttpException
 * class with a specified error message, a reference to the inner exception that is the cause of this exception,
 * href of the item, multistatus response and status of the response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.WebDavHttpException', ITHit.WebDAV.Client.Exceptions.WebDavException, /** @lends ITHit.WebDAV.Client.Exceptions.WebDavHttpException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'WebDavHttpException',

	/**
	 * Multistatus Contains {@link ITHit.WebDAV.Client.Multistatus} with elements that had errors, if multistatus information was available in response.
	 * @api
	 * @type {ITHit.WebDAV.Client.Multistatus}
	 */
	Multistatus: null,

	/**
	 * Http status with wich request failed.
	 * @api
	 * @type {ITHit.WebDAV.Client.HttpStatus}
	 */
	Status: null,

	/**
	 * Uri for which request failed.
	 * @api
	 * @type {string}
	 */
	Uri: null,

	/**
	 * Error contains IError with additional info, if error information was available in response.
	 * @api
	 * @type {ITHit.WebDAV.Client.Error}
	 */
	Error: null,

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.WebDAV.Client.HttpStatus} oStatus Status of response that caused error.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 * @param {ITHit.WebDAV.Client.Error} [oError] Error response containing additional error information.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oStatus, oInnerException, oError) {
		this._super(sMessage, oInnerException);

		this.Multistatus = oMultistatus || new ITHit.WebDAV.Client.Exceptions.Info.Multistatus();
		this.Status = oStatus;
		this.Uri = sHref;
		this.Error = oError;
	}

});


/**
 * Is raised whenever property processing was unsuccessfull. Initializes a new instance of the PropertyException
 * class with a specified error message, a reference to the inner exception that is the cause of this exception,
 * href of the item and multistatus response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.PropertyException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.PropertyException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.PropertyException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'PropertyException',

	/**
	 * Name of the property processing of which caused the exception.
	 * @api
	 * @type {ITHit.WebDAV.Client.PropertyName}
	 */
	PropertyName: null,

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.PropertyName} oPropertyName Name of the property processing of which caused the exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.WebDAV.Client.HttpStatus} oStatus Status of response that caused error.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oPropertyName, oMultistatus, oStatus, oInnerException) {
		this.PropertyName = oPropertyName;
		this._super(sMessage, sHref, oMultistatus, oStatus, oInnerException);
	}

});


/**
 * Thrown when server responded with Property Not Found http response. Initializes a new instance of the
 * PropertyNotFoundException class with a specified error message, a reference to the inner exception that
 * is the cause of this exception, href of the item and multistatus response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException
 * @extends ITHit.WebDAV.Client.Exceptions.PropertyException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException', ITHit.WebDAV.Client.Exceptions.PropertyException, /** @lends ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'PropertyForbiddenException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.PropertyName} oPropertyName Name of the property processing of which caused the exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oPropertyName, oMultistatus, oInnerException) {
		this._super(sMessage, sHref, oPropertyName, oMultistatus, ITHit.WebDAV.Client.HttpStatus.NotFound, oInnerException);
	}

});


/**
 * Thrown when server responded with Property forbidden http response. Initializes a new instance of the
 * PropertyForbiddenException class with a specified error message, a reference to the inner exception
 * that is the cause of this exception, href of the item and multistatus response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.PropertyForbiddenException
 * @extends ITHit.WebDAV.Client.Exceptions.PropertyException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.PropertyForbiddenException', ITHit.WebDAV.Client.Exceptions.PropertyException, /** @lends ITHit.WebDAV.Client.Exceptions.PropertyForbiddenException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'PropertyForbiddenException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.PropertyName} oPropertyName Name of the property processing of which caused the exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oPropertyName, oMultistatus, oInnerException) {
		this._super(sMessage, sHref, oPropertyName, oMultistatus, ITHit.WebDAV.Client.HttpStatus.Forbidden, oInnerException);
	}

});


/**
 * Provides means for finding which properties failed to update.
 * @api
 * @class ITHit.WebDAV.Client.PropertyMultistatusResponse
 * @extends ITHit.WebDAV.Client.MultistatusResponse
 */
ITHit.DefineClass('ITHit.WebDAV.Client.PropertyMultistatusResponse', ITHit.WebDAV.Client.MultistatusResponse, /** @lends ITHit.WebDAV.Client.PropertyMultistatusResponse.prototype */{

	/**
	 * Name of the property, if element is property. Otherwise null.
	 * @api
	 * @type {ITHit.WebDAV.Client.PropertyName}
	 */
	PropertyName: null

});

ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.Info.PropertyMultistatusResponse', ITHit.WebDAV.Client.PropertyMultistatusResponse, /** @lends ITHit.WebDAV.Client.Exceptions.Info.PropertyMultistatusResponse.prototype */{

	/**
	 * Url of the item.
	 * @type {string}
	 */
	Href: null,

	/**
	 * Description of error, if available.
	 * @type {string}
	 */
	Description: null,

	/**
	 * HTTP Status of the operation.
	 * @type {ITHit.WebDAV.Client.HttpStatus}
	 */
	Status: null,

	/**
	 * Name of the property, if element is property. Otherwise null.
	 * @type {ITHit.WebDAV.Client.PropertyMultistatusResponse}
	 */
	PropertyName: null,

	/**
	 * Provides means for finding which properties failed to update.
	 * @constructs
	 * @extends ITHit.WebDAV.Client.PropertyMultistatusResponse
	 */
	constructor: function(sHref, sDescription, oStatus, oPropertyName) {
		this._super();

		this.Href = sHref;
		this.Description = sDescription;
		this.Status = oStatus;
		this.PropertyName = oPropertyName;
	}

});



ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.Info.PropertyMultistatus', ITHit.WebDAV.Client.Multistatus, /** @lends ITHit.WebDAV.Client.Exceptions.Info.PropertyMultistatus.prototype */{

	/**
	 * Gets the generic description, if available.
	 * @type {string}
	 */
	Description: '',

	/**
	 * Array of the errors returned by server.
	 * @type {ITHit.WebDAV.Client.MultistatusResponse[]}
	 */
	Responses: null,

	/**
	 * Provides means for finding which properties failed to update.
	 * Create new instance of PropertyMultistatus class.
	 * @param {ITHit.WebDAV.Client.Exceptions.Info.MultiResponse} [oMultiResponse] MultiResponse object.
	 * @constructs
	 * @extends ITHit.WebDAV.Client.Multistatus
	 */
	constructor: function(oMultiResponse) {
		this.Responses = [];

		if (oMultiResponse) {
			this.Description = oMultiResponse.ResponseDescription;

			for ( var i = 0; i < oMultiResponse.Responses.length; i++ ) {
				var oResponse = oMultiResponse.Responses[i];
				for ( var j = 0; j < oResponse.Propstats.length; j++ ) {
					var oPropstat = oResponse.Propstats[j];
					for ( var k = 0; k < oPropstat.Properties.length; k++ ) {
						this.Responses.push(new ITHit.WebDAV.Client.Exceptions.Info.PropertyMultistatusResponse(oResponse.Href, oPropstat.ResponseDescription, oPropstat.Status, oPropstat.Properties[k].Name));
					}
				}
			}
		}
	}

});

/**
 * Provides functionality for encoding paths and URLs.
 * @class ITHit.WebDAV.Client.Encoder
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Encoder', null, {
	__static: /** @lends ITHit.WebDAV.Client.Encoder */{

		/**
		 * Encodes path presented by string.
		 * @param {string} sText Path to encode.
		 * @returns {string} Encoded path.
		 */
		Encode: ITHit.Encode,

		/**
		 * Decodes path presented by string.
		 * @param {string} sText Path to decode.
		 * @returns {string} Decoded path.
		 */
		Decode: ITHit.Decode,

		EncodeURI: ITHit.EncodeURI,

		DecodeURI: ITHit.DecodeURI

	}
});


/**
 * Method to perform Copy or Move request to a server.
 * @class ITHit.WebDAV.Client.Methods.CopyMove
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.CopyMove', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.CopyMove.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.CopyMove */{

		/**
		 * Modes for CopyMove methods.
		 */
		Mode: {
			Copy: 'Copy',
			Move: 'Move'
		},


		Go: function (oRequest, sMode, sSource, sDestination, bIsCollection, bDeep, bOverwrite, aLockTokens, sHost) {
			// Create request.
			var oWebDavRequest = this.createRequest(oRequest, sMode, sSource, sDestination, bIsCollection, bDeep, bOverwrite, aLockTokens, sHost);
			var oResponse = oWebDavRequest.GetResponse();
			return this._ProcessResponse(oResponse, sSource);
		},

		GoAsync: function (oRequest, sMode, sSource, sDestination, bIsCollection, bDeep, bOverwrite, aLockTokens, sHost, fCallback) {
			// Create request.
			var oWebDavRequest = this.createRequest(oRequest, sMode, sSource, sDestination, bIsCollection, bDeep, bOverwrite, aLockTokens, sHost);

			var that = this;
			oWebDavRequest.GetResponse(function (oAsyncResult) {
				if (!oAsyncResult.IsSuccess) {
					fCallback(new ITHit.WebDAV.Client.AsyncResult(null, false, oAsyncResult.Error));
					return;
				}

				var oResult = that._ProcessResponse(oAsyncResult.Result, sSource);
				fCallback(new ITHit.WebDAV.Client.AsyncResult(oResult, true, null));
			});

			return oWebDavRequest;
		},

		_ProcessResponse: function (oResponse, sSource) {
			// Get appropriate response object.
			var oResp = ITHit.WebDAV.Client.Methods.ResponseFactory.GetResponse(oResponse, sSource);

			// Return result.
			return new ITHit.WebDAV.Client.Methods.CopyMove(oResp);
		},

		createRequest: function (oRequest, sMode, sSource, sDestination, bIsCollection, bDeep, bOverwrite, aLockTokens, sHost) {

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sSource, aLockTokens);

			// TODO: Remove after when encoding special characters on server will be fixed.
			sDestination = ITHit.WebDAV.Client.Encoder.EncodeURI(sDestination).replace(/#/g, '%23').replace(/'/g, '%27');

			if (/^\//.test(sDestination)) {
				sDestination = sHost + sDestination.substr(1);
			}

			// Add headers
			oWebDavRequest.Method((sMode == ITHit.WebDAV.Client.Methods.CopyMove.Mode.Copy) ? 'COPY' : 'MOVE');
			oWebDavRequest.Headers.Add('Content-Type', 'text/xml; charset="utf-8"');
			oWebDavRequest.Headers.Add('Destination', ITHit.DecodeHost(sDestination));
			oWebDavRequest.Headers.Add('Overwrite', bOverwrite ? "T" : "F");

			// Set depth property if specified by input parameters.
			if (bIsCollection && (sMode == ITHit.WebDAV.Client.Methods.CopyMove.Mode.Copy)) {
				// Built-in IIS 8.0 WebDAV does not support Depth: Infinity
				if (!bDeep) {
					oWebDavRequest.Headers.Add("Depth", ITHit.WebDAV.Client.Depth.Zero.Value);
				}
			}

			// Create XML DOM document.
			var oWriter = new ITHit.XMLDoc();

			// Create XML document.
			var propBehav = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'propertybehavior');
			var keepAlive = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'keepalive')
			keepAlive.appendChild(oWriter.createTextNode('*'));
			propBehav.appendChild(keepAlive);
			oWriter.appendChild(propBehav);

			// Add XML document as request body.
			oWebDavRequest.Body(oWriter);

			// Return request object.
			return oWebDavRequest;
		}

	}
});


/**
 * @class ITHit.WebDAV.Client.Methods.Delete
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Delete', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Delete.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Delete */{

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param oLockTokens
		 * @param sHost
		 * @returns {*}
		 */
		Go: function (oRequest, sHref, oLockTokens, sHost) {
			return this._super.apply(this, arguments);
		},

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param oLockTokens
		 * @param sHost
		 * @param fCallback
		 * @returns {*}
		 */
		GoAsync: function (oRequest, sHref, oLockTokens, sHost, fCallback) {
			return this._super.apply(this, arguments);
		},

		_CreateRequest: function (oRequest, sHref, oLockTokens, sHost) {

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref, oLockTokens);

			// Set method.
			oWebDavRequest.Method('DELETE');

			// Return request object.
			return oWebDavRequest;
		},

		_ProcessResponse: function (oResponse, sHref) {
			// Get appropriate response object.
			var oResp = ITHit.WebDAV.Client.Methods.ResponseFactory.GetResponse(oResponse, sHref);

			return this._super(oResp);
		}

	}
});


/**
 * @class ITHit.WebDAV.Client.Methods.Proppatch
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Proppatch', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Proppatch.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Proppatch */{

		Go: function (oRequest, sHref, aPropsToAddOrUpdate, aPropsToDelete, sLockToken, sHost) {

			// Create request.
			var oWebDavRequest = ITHit.WebDAV.Client.Methods.Proppatch.createRequest(
				oRequest,
				sHref,
				aPropsToAddOrUpdate,
				aPropsToDelete,
				sLockToken,
				sHost
			);

			// Get response.
			var oResult = oWebDavRequest.GetResponse();

			// Return response object.
			return this._ProcessResponse(oResult);
		},

		GoAsync: function (oRequest, sHref, aPropsToAddOrUpdate, aPropsToDelete, sLockToken, sHost, fCallback) {
			// Create request.
			var oWebDavRequest = ITHit.WebDAV.Client.Methods.Proppatch.createRequest(
				oRequest,
				sHref,
				aPropsToAddOrUpdate,
				aPropsToDelete,
				sLockToken,
				sHost
			);

			// Get response.
			var that = this;
			oWebDavRequest.GetResponse(function (oAsyncResult) {

				if (!oAsyncResult.IsSuccess) {
					fCallback(new ITHit.WebDAV.Client.AsyncResult(null, false, oAsyncResult.Error));
					return;
				}

				var oResult = that._ProcessResponse(oAsyncResult.Result, sHref);
				fCallback(new ITHit.WebDAV.Client.AsyncResult(oResult, true, null));
			});

		},

		_ProcessResponse: function (oResponse, sHref) {
			// Get response data.
			var oResponseData = oResponse.GetResponseStream();

			// Return response object.
			return new ITHit.WebDAV.Client.Methods.Proppatch(new ITHit.WebDAV.Client.Methods.MultiResponse(oResponseData, sHref));
		},

		ItemExists: function (aArr) {

			if (aArr && aArr.length) {
				for (var i = 0; i < aArr.length; i++) {
					if (aArr[i]) {
						return true;
					}
				}
			}

			return false;
		},

		createRequest: function (oRequest, sHref, aPropsToAddOrUpdate, aPropsToDelete, sLockToken, sHost) {

			// Assign default value if needed.
			sLockToken = sLockToken || null;

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref, sLockToken);
			oWebDavRequest.Method('PROPPATCH');
			oWebDavRequest.Headers.Add('Content-Type', 'text/xml; charset="utf-8"');

			// Create XML DOM document.
			var oWriter = new ITHit.XMLDoc();

			// Create XML request.
			var propUpd = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'propertyupdate');

			// Check whether properties to add or update are specified.
			if (ITHit.WebDAV.Client.Methods.Proppatch.ItemExists(aPropsToAddOrUpdate)) {
				var set = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'set');

				for (var i = 0; i < aPropsToAddOrUpdate.length; i++) {
					if (aPropsToAddOrUpdate[i]) {
						var prop = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'prop');
						prop.appendChild(aPropsToAddOrUpdate[i].Value);
						set.appendChild(prop);
					}
				}
				propUpd.appendChild(set);
			}

			// Check whether properties to delete are specified.
			if (ITHit.WebDAV.Client.Methods.Proppatch.ItemExists(aPropsToDelete)) {
				var remove = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'remove');
				var prop = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'prop');
				for (var i = 0; i < aPropsToDelete.length; i++) {
					if (aPropsToDelete[i]) {
						var elem = oWriter.createElementNS(aPropsToDelete[i].NamespaceUri, aPropsToDelete[i].Name);
						prop.appendChild(elem);
					}
				}
				remove.appendChild(prop);
				propUpd.appendChild(remove);
			}

			oWriter.appendChild(propUpd);
			oWebDavRequest.Body(oWriter);

			return oWebDavRequest;
		}

	}
});

/**
 * Scope of the lock.
 * Represents exclusive or shared lock.
 * @api
 * @enum {string}
 * @class ITHit.WebDAV.Client.LockScope
 */
ITHit.DefineClass('ITHit.WebDAV.Client.LockScope', null, {
	__static: /** @lends ITHit.WebDAV.Client.LockScope */{

		/**
		 * Exclusive lock. No one else can obtain the lock.
		 * @api
		 * @type {string}
		 */
		Exclusive: 'Exclusive',

		/**
		 * Shared lock. It will be possible for another clients to get the shared locks.
		 * @api
		 * @property {string}
		 */
		Shared: 'Shared'

	}
});


/**
 * Represents pair of resource uri - lock token. Is used to access locked resources.
 * @api
 * @class ITHit.WebDAV.Client.LockUriTokenPair
 */
ITHit.DefineClass('ITHit.WebDAV.Client.LockUriTokenPair', null, /** @lends ITHit.WebDAV.Client.LockUriTokenPair.prototype */{

	/**
	 * Path to the locked resource.
	 * @api
	 * @type {string}
	 */
	Href: null,

	/**
	 * Lock token.
	 * @api
	 * @type {string}
	 */
	LockToken: null,

	/**
	 * Initializes new instance of LockUriTokenPair.
	 * @param {string} sHref Path to the locked resource.
	 * @param {string} sLockToken Lock token.
	 * @throws ITHit.Exceptions.ArgumentNullException Whether sHref is null or sLockScope is null or empty.
	 */
	constructor: function(sHref, sLockToken) {
		ITHit.WebDAV.Client.WebDavUtil.VerifyArgumentNotNull(sHref, "href");
		ITHit.WebDAV.Client.WebDavUtil.VerifyArgumentNotNullOrEmpty(sLockToken, "lockToken");

		this.Href = sHref;
		this.LockToken = sLockToken;
	},

	toString: function() {
		return this.LockToken;
	}

});


/**
 * Information about lock set on an item.
 * @api
 * @class ITHit.WebDAV.Client.LockInfo
 */
ITHit.DefineClass('ITHit.WebDAV.Client.LockInfo', null, /** @lends ITHit.WebDAV.Client.LockInfo.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.LockInfo */{

		/**
		 * Parses activeLocks from lockNode.
		 * @param {ITHit.XMLDoc} oElement Node containing XML Element with activeLock node.
		 * @param {string} sHref Request's URI.
		 * @returns {ITHit.WebDAV.Client.LockInfo} Information about active locks.
		 */
		ParseLockInfo: function(oElement, sHref) {

			// Declare resolver for namespace.
			var oResolver = new ITHit.XPath.resolver();
			oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);

			// Declare node variable.
			var oNode;

			// Get lock scope.
			if (!(oNode = ITHit.XPath.selectSingleNode('d:lockscope', oElement, oResolver))) {
				throw new ITHit.WebDAV.Client.Exceptions.WebDavException(ITHit.Phrases.Exceptions.ActiveLockDoesntContainLockscope);
			}

			// Detect lock scope
			var oLockScope = null;
			var oLockScopeChilds = oNode.childNodes();
			for (var i = 0, l = oLockScopeChilds.length; i < l; i++) {
				if (oLockScopeChilds[i].nodeType() === 1) {
					oLockScope = oLockScopeChilds[i].localName();
					break;
				}
			}
			switch (oLockScope) {
				case 'shared':
					oLockScope = ITHit.WebDAV.Client.LockScope.Shared;
					break;

				case 'exclusive':
					oLockScope = ITHit.WebDAV.Client.LockScope.Exclusive;
					break;
			}

			// Get depth.
			if ( !(oNode = ITHit.XPath.selectSingleNode('d:depth', oElement, oResolver)) ) {
				throw new ITHit.WebDAV.Client.Exceptions.WebDavException(ITHit.Phrases.Exceptions.ActiveLockDoesntContainDepth);
			}

			var oDepthValue = ITHit.WebDAV.Client.Depth.Parse(oNode.firstChild().nodeValue());
			var bDeep = (oDepthValue == ITHit.WebDAV.Client.Depth.Infinity);

			// Get owner.
			var sOwner = null;
			if ( oNode = ITHit.XPath.selectSingleNode('d:owner', oElement, oResolver) ) {
				sOwner = oNode.firstChild().nodeValue();
			}

			// Get timeout.
			var iTimeOut = -1;
			if ( oNode = ITHit.XPath.selectSingleNode('d:timeout', oElement, oResolver) ) {
				var sTimeOut = oNode.firstChild().nodeValue();

				if ('infinite' != sTimeOut.toLowerCase()) {
					if (-1 != sTimeOut.toLowerCase().indexOf('second-')) {
						sTimeOut = sTimeOut.substr(7);
					}
					var iTimeOut = parseInt(sTimeOut);
				}
			}

			// Get lock token.

			var oLockToken = null;
			if ( oNode = ITHit.XPath.selectSingleNode('d:locktoken', oElement, oResolver) ) {
				var sLockTokenText = ITHit.XPath.selectSingleNode('d:href', oNode, oResolver).firstChild().nodeValue();
				sLockTokenText = sLockTokenText.replace(ITHit.WebDAV.Client.DavConstants.OpaqueLockToken, '');
				oLockToken = new ITHit.WebDAV.Client.LockUriTokenPair(sHref, sLockTokenText);
			}

			return new ITHit.WebDAV.Client.LockInfo(oLockScope, bDeep, sOwner, iTimeOut, oLockToken);
		},

		/**
		 * Parses activeLocks from lockNode.
		 * @param {ITHit.XMLDoc} oElement Node containing XML Element with activeLock node.
		 * @param {string} sHref Requests URI
		 * @returns {Array} Information about active locks.
		 */
		ParseLockDiscovery: function(oElement, sHref) {

			// Declare variable list of locks.
			var aLocks = [];

			// Get a list of active lockes nodes.
			var aSearchedLocks = oElement.getElementsByTagNameNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'activelock');

			for (var i = 0; i < aSearchedLocks.length; i++) {
				aLocks.push(ITHit.WebDAV.Client.LockInfo.ParseLockInfo(aSearchedLocks[i], sHref));
			}

			return aLocks;
		}
	},

	/**
	 * Scope of the lock.
	 * @api
	 * @type {ITHit.WebDAV.Client.LockScope}
	 */
	LockScope: null,

	/**
	 * Whether lock is set on item's children.
	 * @api
	 * @type {boolean}
	 */
	Deep: null,

	/**
	 * Timeout until lock expires.
	 * @api
	 * @type {number}
	 */
	TimeOut: null,

	/**
	 * Owner's name.
	 * @api
	 * @type {string}
	 */
	Owner: null,

	/**
	 * Lock token.
	 * @api
	 * @type {ITHit.WebDAV.Client.LockUriTokenPair}
	 */
	LockToken: null,

	/**
	 * Initializes new instance of LockInfo.
	 * @param {ITHit.WebDAV.Client.LockScope} oLockScope Scope of the lock.
	 * @param {boolean}   bDeep Whether lock is set on item's children.
	 * @param {string} sOwner Owner's name.
	 * @param {number} iTimeOut Timeout until lock expires.
	 * @param {ITHit.WebDAV.Client.LockUriTokenPair} oLockToken Lock token.
	 */
	constructor: function(oLockScope, bDeep, sOwner, iTimeOut, oLockToken) {
		this.LockScope = oLockScope;
		this.Deep = bDeep;
		this.TimeOut = iTimeOut;
		this.Owner = sOwner;
		this.LockToken = oLockToken;
	}

});


/**
 * @class ITHit.WebDAV.Client.Methods.Lock
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Lock', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Lock.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Lock */{

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param iTimeout
		 * @param sLockTokenOrScope
		 * @param sHost
		 * @param bDeep
		 * @param sOwner
		 * @returns {*}
		 * @constructor
		 */
		Go: function (oRequest, sHref, iTimeout, sLockTokenOrScope, sHost, bDeep, sOwner) {
			return this._super.apply(this, arguments);
		},

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param iTimeout
		 * @param sLockTokenOrScope
		 * @param sHost
		 * @param bDeep
		 * @param sOwner
		 * @param fCallback
		 * @returns {*}
		 * @constructor
		 */
		GoAsync: function (oRequest, sHref, iTimeout, sLockTokenOrScope, sHost, bDeep, sOwner, fCallback) {
			return this._super.apply(this, arguments);
		},

		_CreateRequest: function (oRequest, sHref, iTimeout, sLockTokenOrScope, sHost, bDeep, sOwner) {
			// Passed lock scope.
			var sLockScope = sLockTokenOrScope;

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref);
			oWebDavRequest.Method('LOCK');

			// Add headers.
			oWebDavRequest.Headers.Add('Timeout',
				(-1 === iTimeout)
					? 'Infinite'
					: 'Second-' + parseInt(iTimeout)
			);
			oWebDavRequest.Headers.Add('Depth', bDeep ? ITHit.WebDAV.Client.Depth.Infinity.Value : ITHit.WebDAV.Client.Depth.Zero.Value);
			oWebDavRequest.Headers.Add('Content-Type', 'text/xml; charset="utf-8"');

			// Create XML DOM document object.
			var oWriter = new ITHit.XMLDoc();

			// Get namespace for XML elements.
			var sNamespaceUri = ITHit.WebDAV.Client.DavConstants.NamespaceUri;

			// Create root element.
			var lockInfo = oWriter.createElementNS(sNamespaceUri, 'lockinfo');

			// Create elements.
			var lockScope = oWriter.createElementNS(sNamespaceUri, 'lockscope');
			var lockScopeData = oWriter.createElementNS(sNamespaceUri, sLockScope.toLowerCase());
			lockScope.appendChild(lockScopeData);

			var lockType = oWriter.createElementNS(sNamespaceUri, 'locktype');
			var write = oWriter.createElementNS(sNamespaceUri, 'write');
			lockType.appendChild(write);

			var owner = oWriter.createElementNS(sNamespaceUri, 'owner');
			owner.appendChild(oWriter.createTextNode(sOwner));

			lockInfo.appendChild(lockScope);
			lockInfo.appendChild(lockType);
			lockInfo.appendChild(owner);

			oWriter.appendChild(lockInfo);

			// Add XML document as request body.
			oWebDavRequest.Body(oWriter);

			return oWebDavRequest;
		}

	},

	/**
	 * @type {ITHit.WebDAV.Client.LockInfo}
	 */
	LockInfo: null,

	_Init: function () {
		// Get response data as string.
		var oXmlDoc = this.Response.GetResponseStream();

		// Create namespace resolver.
		var oResolver = new ITHit.XPath.resolver();
		oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);

		// Select property element.
		var oProp = new ITHit.WebDAV.Client.Property(ITHit.XPath.selectSingleNode('/d:prop', oXmlDoc, oResolver));

		try {
			// Parse property element.
			var oInfoList = new ITHit.WebDAV.Client.LockInfo.ParseLockDiscovery(oProp.Value, this.Href);

			// Check length of selected elements.
			if (oInfoList.length !== 1) {
				throw new ITHit.WebDAV.Client.Exceptions.WebDavException(ITHit.Phrases.UnableToParseLockInfoResponse);
			}

			// Select property element.
			this.LockInfo = oInfoList[0];

			// Exception had happened.
		} catch (e) {
			throw new ITHit.WebDAV.Client.Exceptions.PropertyException(
				ITHit.Phrases.Exceptions.ParsingPropertiesException,
				this.Href,
				oProp.Name,
				null,
				ITHit.WebDAV.Client.HttpStatus.OK,
				e
			);
		}
	}
});


/**
 * @class ITHit.WebDAV.Client.Methods.LockRefresh
 * @extends ITHit.WebDAV.Client.Methods.Lock
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.LockRefresh', ITHit.WebDAV.Client.Methods.Lock, /** @lends ITHit.WebDAV.Client.Methods.LockRefresh.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.LockRefresh */{

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param iTimeout
		 * @param sLockTokenOrScope
		 * @param sHost
		 * @param bDeep
		 * @param sOwner
		 * @returns {*}
		 * @constructor
		 */
		Go: function (oRequest, sHref, iTimeout, sLockTokenOrScope, sHost, bDeep, sOwner) {
			return this._super.apply(this, arguments);
		},

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param iTimeout
		 * @param sLockTokenOrScope
		 * @param sHost
		 * @param bDeep
		 * @param sOwner
		 * @param fCallback
		 * @returns {*}
		 * @constructor
		 */
		GoAsync: function (oRequest, sHref, iTimeout, sLockTokenOrScope, sHost, bDeep, sOwner, fCallback) {
			return this._super.apply(this, arguments);
		},

		_CreateRequest: function (oRequest, sHref, iTimeout, sLockTokenOrScope, sHost, bDeep, sOwner) {

			// Passed lock token.
			var sLockToken = sLockTokenOrScope;

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref, sLockToken);
			oWebDavRequest.Method('LOCK');

			// Add header.
			oWebDavRequest.Headers.Add('Timeout',
				(-1 == iTimeout)
					? 'Infinite'
					: 'Second-' + parseInt(iTimeout)
			);

			oWebDavRequest.Body('');

			return oWebDavRequest;
		}

	}
});


/**
 * @class ITHit.WebDAV.Client.Methods.Unlock
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Unlock', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Unlock.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Unlock */{

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param sLockToken
		 * @param sHost
		 * @returns {ITHit.WebDAV.Client.Methods.Unlock}
		 */
		Go: function (oRequest, sHref, sLockToken, sHost) {
			return this._super.apply(this, arguments);
		},

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param sLockToken
		 * @param sHost
		 * @param fCallback
		 * @returns {*}
		 */
		GoAsync: function (oRequest, sHref, sLockToken, sHost, fCallback) {
			return this._super.apply(this, arguments);
		},

		_ProcessResponse: function (oResponse, sHref) {
			// Get appropriate response object.
			var oResp = new ITHit.WebDAV.Client.Methods.SingleResponse(oResponse);

			return this._super(oResp);
		},

		_CreateRequest: function (oRequest, sHref, sLockToken, sHost) {

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref);
			oWebDavRequest.Method('UNLOCK');

			// Add header.
			oWebDavRequest.Headers.Add('Lock-Token', '<' + ITHit.WebDAV.Client.DavConstants.OpaqueLockToken + sLockToken + '>');

			return oWebDavRequest;
		}

	}
});


/**
 * Options of an item, described by supported HTTP extensions.
 * @api
 * @class ITHit.WebDAV.Client.OptionsInfo
 */
ITHit.DefineClass('ITHit.WebDAV.Client.OptionsInfo', null, /** @lends ITHit.WebDAV.Client.OptionsInfo.prototype */{

	/**
	 * Features supported by WebDAV server. See Features Enumeration {@link ITHit.WebDAV.Client.Features}.
	 * @api
	 * @type {number}
	 */
	Features: null,

	/**
	 * A nonstandard header meaning the server supports WebDAV protocol.
	 * @type {boolean}
	 */
	MsAuthorViaDav: null,

	/**
	 * DeltaV Version History compliant item.
	 * @type {number}
	 */
	VersionControl: null,

	/**
	 * The item supports search
	 * @type {boolean}
	 */
	Search: null,

	/**
	 * Server version (engine header)
	 * @type {string}
	 */
	ServerVersion: '',

	/**
	 * Create new instance of OptionsInfo class.
	 * @param {number} iFeatures Classes of WebDAV protocol supported by the item.
	 * @param {boolean} bMsAuthorViaDav A nonstandard header meaning the server supports WebDAV protocol.
	 * @param {number} iVersionControl
	 * @param {boolean} bSearchSupported
	 * @param {string} sServerVersion
	 */
	constructor: function(iFeatures, bMsAuthorViaDav, iVersionControl, bSearchSupported, sServerVersion) {
		this.Features = iFeatures;
		this.MsAuthorViaDav = bMsAuthorViaDav;
		this.VersionControl = iVersionControl;
		this.Search = bSearchSupported;
		this.ServerVersion = sServerVersion;
	}

});

/**
 * Represents features supported by WebDAV server.
 * @api
 * @enum {number}
 * @class ITHit.WebDAV.Client.Features
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Features', null, {
	__static: /** @lends ITHit.WebDAV.Client.Features */{

		/**
		 * WebDAV Class 1 compliant item.
		 * Class 1 items does not support locking.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		Class1: 1,

		/**
		 * WebDAV Class 2 compliant item.
		 * Class 2 items support locking.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		Class2: 2,

		/**
		 * WebDAV Class 3 compliant item.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		Class3: 3,

		/**
		 * WevDAV paging compliant item.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		VersionControl: 4,

	    /**
		 * DeltaV version-control compliant item.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		Paging: 8,

		/**
		 * Checkout-in-place item support check out, check in and uncheckout operations.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		CheckoutInPlace: 16,

		/**
		 * DeltaV Version History compliant item.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		VersionHistory: 32,

		/**
		 * DeltaV Update compliant item.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		Update: 64,

		/**
		 * The item supports resumable upload.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		ResumableUpload: 128,

		/**
		 * The item supports resumable download.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		ResumableDownload: 256,

		/**
		 * The item supports search.
		 * @api
		 * @readonly
		 * @type {number}
		 */
		Dasl: 512,

	    /**
		 * The item supports GSuite editing.
		 * @api
		 * @readonly
		 * @type {number}
		 */
        GSuite: 1024
	}
});


ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Options', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Options.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Options */{

		Go: function (oRequest, sHref, sHost) {
			return this.GoAsync(oRequest, sHref, sHost);
		},

		GoAsync: function (oRequest, sHref, sHost, fCallback) {

			// Create request.
			var oWebDavRequest = ITHit.WebDAV.Client.Methods.Options.createRequest(oRequest, sHref, sHost);

			var self = this;
			var fOnResponse = typeof fCallback === 'function'
				? function (oResult) {
				self._GoCallback(oRequest, sHref, oResult, fCallback)
			}
				: null;

			// Make request.
			var oResponse = oWebDavRequest.GetResponse(fOnResponse);

			if (typeof fCallback !== 'function') {
				var oResult = new ITHit.WebDAV.Client.AsyncResult(oResponse, oResponse != null, null);
				return this._GoCallback(oRequest, sHref, oResult, fCallback);
			} else {
				return oWebDavRequest;
			}
		},

		_GoCallback: function (oRequest, sHref, oResult, fCallback) {

			var oResponse = oResult;
			var bSuccess = true;
			var oError = null;

			if (oResult instanceof ITHit.WebDAV.Client.AsyncResult) {
				oResponse = oResult.Result;
				bSuccess = oResult.IsSuccess;
				oError = oResult.Error;
			}

			var oOptions = null;
			if (bSuccess) {
				// Get options.
				var oOptions = new ITHit.WebDAV.Client.Methods.Options(oResponse);
			}

			// Return response.
			if (typeof fCallback === 'function') {
				var oOptionsResult = new ITHit.WebDAV.Client.AsyncResult(oOptions, bSuccess, oError);
				fCallback.call(this, oOptionsResult);
			} else {
				return oOptions;
			}
		},

		createRequest: function (oRequest, sHref, sHost) {

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref);

			// Set method.
			oWebDavRequest.Method('OPTIONS');

			// Return request object.
			return oWebDavRequest;
		}

	},

	ItemOptions: null,

	/**
	 * Method to perform Options request to a server.
	 * Create new instance of Options class.
	 * @constructs
	 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
	 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
	 */
	constructor: function (oResponse) {
		this._super(oResponse);

		// Get DAV request header.
		var sDav = oResponse._Response.GetResponseHeader('dav', true);

		// Get version of WebDAV server.
		var iFeatures = 0;
		var iVersionControl = 0;
		if (sDav) {
			if (-1 != sDav.indexOf('2')) {
				iFeatures = ITHit.WebDAV.Client.Features.Class1 + ITHit.WebDAV.Client.Features.Class2;
			} else if (-1 != sDav.indexOf('1')) {
				iFeatures = ITHit.WebDAV.Client.Features.Class1;
			}

			if (-1 != sDav.indexOf('version-control')) {
				iVersionControl = ITHit.WebDAV.Client.Features.VersionControl;
			}

			// Whether server supports ITHit Resumable Upload.
			if (-1 != sDav.indexOf('resumable-upload')) {
				iFeatures += ITHit.WebDAV.Client.Features.ResumableUpload;
			}

		    // Whether server supports ITHit Paging.
			if (-1 != sDav.indexOf('paging')) {
			    iFeatures += ITHit.WebDAV.Client.Features.Paging;
			}		    
		}

	    // Whether server supports GSuite editing.
		var sGsuite = oResponse._Response.GetResponseHeader('gsuite', true)
		if (sGsuite && -1 != sGsuite.toLowerCase().indexOf('gedit')) {
		    iFeatures += ITHit.WebDAV.Client.Features.GSuite;
		}

		var bMsAuthorViaDav = false;
		var sMsAuthorViaHeader = oResponse._Response.GetResponseHeader('ms-author-via', true);

		if (sMsAuthorViaHeader && (-1 != sMsAuthorViaHeader.toLowerCase().indexOf('dav'))) {
			bMsAuthorViaDav = true;
		}

		// Detect search support
		var iSearchSupported = false;
		var sAllowHeader = oResponse._Response.GetResponseHeader('allow', true) || '';
		var aAllowList = sAllowHeader.toLowerCase().split(/[^a-z-_]+/);
		for (var i = 0, l = aAllowList.length; i < l; i++) {
			if (aAllowList[i] === 'search') {
				iSearchSupported = true;
				iFeatures += ITHit.WebDAV.Client.Features.Dasl;
				break;
			}
		}

		// Get server version
		var sServerVersion = oResponse._Response.GetResponseHeader('x-engine', true);

		this.ItemOptions = new ITHit.WebDAV.Client.OptionsInfo(iFeatures, bMsAuthorViaDav, iVersionControl, iSearchSupported, sServerVersion);
	}
});


ITHit.oNS = ITHit.Declare('ITHit.Exceptions');

/*
 * Wrong expression.
 * @class ITHit.Exceptions.ExpressionException
 * @extends ITHit.Exception
 */
/*
 * Initializes a new instance of the ExpressionException class with a specified error message.
 * @constructor ExpressionException
 * 
 * @param {String} sMessage  The error message that explains the reason for the exception.
 */
ITHit.oNS.ExpressionException = function(sMessage) {
	
	// Inheritance definition.
	ITHit.Exceptions.ExpressionException.baseConstructor.call(this, sMessage);
}

// Extend class.
ITHit.Extend(ITHit.oNS.ExpressionException, ITHit.Exception);

// Exception name.
ITHit.oNS.ExpressionException.prototype.Name = 'ExpressionException';

/**
 * Information about file upload progress.
 * @class ITHit.WebDAV.Client.UploadProgressInfo
 */
ITHit.DefineClass('ITHit.WebDAV.Client.UploadProgressInfo', null, /** @lends ITHit.WebDAV.Client.UploadProgressInfo.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.UploadProgressInfo */{

		GetUploadProgress: function(oMultiResponse) {

			var aUploadInfo    = [];

			if (!ITHit.WebDAV.Client.UploadProgressInfo.PropNames) {
				ITHit.WebDAV.Client.UploadProgressInfo.PropNames = [
					new ITHit.WebDAV.Client.PropertyName('bytes-uploaded', 'ithit'),
					new ITHit.WebDAV.Client.PropertyName('last-chunk-saved', 'ithit'),
					new ITHit.WebDAV.Client.PropertyName('total-content-length', 'ithit')
				];
			}

			for (var i = 0, oResponse; oResponse = oMultiResponse.Responses[i]; i++) {
				for (var j = 0, oPropstat; oPropstat = oResponse.Propstats[j]; j++) {

					var oFoundedProps = [];

					for (var k = 0, oProp; oProp = oPropstat.Properties[k]; k++) {

						// Bytes uploaded.
						if (oProp.Name.Equals(ITHit.WebDAV.Client.UploadProgressInfo.PropNames[0])) {
							oFoundedProps[0] = oProp.Value;
						}
						// Last chunk saved.
						else if (oProp.Name.Equals(ITHit.WebDAV.Client.UploadProgressInfo.PropNames[1])) {
							oFoundedProps[1] = oProp.Value;
						}
						// Percent uploaded.
						else if (oProp.Name.Equals(ITHit.WebDAV.Client.UploadProgressInfo.PropNames[2])) {
							oFoundedProps[2] = oProp.Value;
						}
					}

					if (!oFoundedProps[0] || !oFoundedProps[1] || !oFoundedProps[2]) {
						throw new ITHit.Exception(ITHit.Phrases.Exceptions.NotAllPropertiesReceivedForUploadProgress.Paste(oResponse.Href));
					}

					aUploadInfo.push(new ITHit.WebDAV.Client.UploadProgressInfo(oResponse.Href, parseInt(oFoundedProps[0].firstChild().nodeValue()), parseInt(oFoundedProps[2].firstChild().nodeValue()), ITHit.WebDAV.Client.HierarchyItem.GetDate(oFoundedProps[1].firstChild().nodeValue())));
				}
			}

			return aUploadInfo;
		}

	},

	/**
	 * Item path on the server.
	 * @api
	 * @type {string}
	 */
	Href: null,

	/**
	 * Amount of bytes successfully uploaded to server.
	 * @api
	 * @type {number}
	 */
	BytesUploaded: null,

	/**
	 * Total file size.
	 * @api
	 * @type {number}
	 */
	TotalContentLength: null,

	/**
	 * The date and time when the last chunk of file was saved on server side.
	 * @api
	 * @type {Date}
	 */
	LastChunkSaved: null,

	/**
	 * @param {string} sHref Item's path.
	 * @param {number} iBytesUploaded Uploaded bytes.
	 * @param {number} iContentLength Total file size.
	 * @param {Date} [oLastChunkSaved] Last chunk save date.
	 */
	constructor: function(sHref, iBytesUploaded, iContentLength, oLastChunkSaved) {

		if (!ITHit.Utils.IsString(sHref) || !sHref) {
			throw new ITHit.Exceptions.ArgumentException(ITHit.Phrases.Exceptions.WrongHref.Paste(), sHref);
		}

		if (!ITHit.Utils.IsInteger(iBytesUploaded)) {
			throw new ITHit.Exceptions.ArgumentException(ITHit.Phrases.Exceptions.WrongUploadedBytesType, iBytesUploaded);
		}

		if (!ITHit.Utils.IsInteger(iContentLength)) {
			throw new ITHit.Exceptions.ArgumentException(ITHit.Phrases.Exceptions.WrongContentLengthType, iContentLength);
		}

		if (iBytesUploaded > iContentLength) {
			throw new ITHit.Exceptions.ExpressionException(ITHit.Phrases.Exceptions.BytesUploadedIsMoreThanTotalFileContentLength);
		}

		this.Href               = sHref;
		this.BytesUploaded      = iBytesUploaded;
		this.TotalContentLength = iContentLength;
		this.LastChunkSaved     = oLastChunkSaved;
	}

});


ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Report', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Report.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Report */{

		ReportType: {

			/**
			 * Report return upload progress info (default)
			 * @type {string}
			 */
			UploadProgress: 'UploadProgress',

			/**
			 * Report return versions tree
			 * @type {string}
			 */
			VersionsTree: 'VersionsTree'
		},

		Go: function (oRequest, sHref, sHost, reportType, aProperties) {
			return this.GoAsync(oRequest, sHref, sHost, reportType, aProperties);
		},

		GoAsync: function (oRequest, sHref, sHost, reportType, aProperties, fCallback) {

			// by default
			if (!reportType) {
				reportType = ITHit.WebDAV.Client.Methods.Report.ReportType.UploadProgress;
			}

			// Create request.
			var oWebDavRequest = ITHit.WebDAV.Client.Methods.Report.createRequest(oRequest, sHref, sHost, reportType, aProperties);


			var self = this;
			var fOnResponse = typeof fCallback === 'function'
				? function (oResult) {
				self._GoCallback(sHref, oResult, reportType, fCallback)
			}
				: null;

			// Make request.
			var oResponse = oWebDavRequest.GetResponse(fOnResponse);

			if (typeof fCallback !== 'function') {
				var oResult = new ITHit.WebDAV.Client.AsyncResult(oResponse, oResponse != null, null);
				return this._GoCallback(sHref, oResult, reportType, fCallback);
			} else {
				return oWebDavRequest;
			}
		},

		_GoCallback: function (sHref, oResult, reportType, fCallback) {

			var oResponse = oResult;
			var bSuccess = true;
			var oError = null;

			if (oResult instanceof ITHit.WebDAV.Client.AsyncResult) {
				oResponse = oResult.Result;
				bSuccess = oResult.IsSuccess;
				oError = oResult.Error;
			}

			var oReport = null;
			if (bSuccess) {
				// Receive data.
				var oResponseData = oResponse.GetResponseStream();

				oReport = new ITHit.WebDAV.Client.Methods.Report(new ITHit.WebDAV.Client.Methods.MultiResponse(oResponseData, sHref), reportType);
			}

			// Return response.
			if (typeof fCallback === 'function') {
				var oReportResult = new ITHit.WebDAV.Client.AsyncResult(oReport, bSuccess, oError);
				fCallback.call(this, oReportResult);
			} else {
				return oReport;
			}
		},

		createRequest: function (oRequest, sHref, sHost, reportType, aProperties) {

			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref);

			oWebDavRequest.Method('REPORT');
			oWebDavRequest.Headers.Add('Content-Type', 'text/xml; charset="utf-8"');

			// Create XML DOM document.
			var oWriter = new ITHit.XMLDoc();

			switch (reportType) {
				case ITHit.WebDAV.Client.Methods.Report.ReportType.UploadProgress:
					var oElem = oWriter.createElementNS('ithit', 'upload-progress');
					oWriter.appendChild(oElem);
					break;

				case ITHit.WebDAV.Client.Methods.Report.ReportType.VersionsTree:
					// Create root element.
					var oVersionTreeElement = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'version-tree');

					// All properties.
					if (!aProperties || !aProperties.length) {
						var propEl = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'allprop');

						// Selected properties.
					} else {
						var propEl = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'prop');
						for (var i = 0; i < aProperties.length; i++) {
							var prop = oWriter.createElementNS(aProperties[i].NamespaceUri, aProperties[i].Name);
							propEl.appendChild(prop);
						}
					}

					// Append created child nodes.
					oVersionTreeElement.appendChild(propEl);
					oWriter.appendChild(oVersionTreeElement);
					break;
			}

			oWebDavRequest.Body(oWriter);

			// Return request object.
			return oWebDavRequest;
		}

	},

	/**
	 * @constructs
	 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
	 * @param {string} reportType
	 */
	constructor: function (oResponse, reportType) {
		this._super(oResponse);

		switch (reportType) {
			case ITHit.WebDAV.Client.Methods.Report.ReportType.UploadProgress:
				return ITHit.WebDAV.Client.UploadProgressInfo.GetUploadProgress(oResponse);
		}
	}
});


;
(function() {

	/**
	 * Represents one WebDAV item (file, folder or lock-null).
	 * @api
	 * @class ITHit.WebDAV.Client.HierarchyItem
	 */
	var self = ITHit.DefineClass('ITHit.WebDAV.Client.HierarchyItem', null, /** @lends ITHit.WebDAV.Client.HierarchyItem.prototype */{

		__static: /** @lends ITHit.WebDAV.Client.HierarchyItem */{

			GetRequestProperties: function() {
				return ITHit.WebDAV.Client.File.GetRequestProperties();
			},

			GetCustomRequestProperties: function(aCustomProperties) {
				// Set node properties for selection.
				var aProperties = this.GetRequestProperties();

				// Normalize additional properties (clean duplicates)
				var aNormalizedAdditionalProperties = [];
				for (var i = 0, l = aCustomProperties.length; i < l; i++) {
					var oProperty = aCustomProperties[i];
					var bFinedInDefaults = false;

					// Find in defaults
					for (var i2 = 0, l2 = aProperties.length; i2 < l2; i2++) {
						if (oProperty.Equals(aProperties[i2])) {
							bFinedInDefaults = true;
							break;
						}
					}

					if (!bFinedInDefaults) {
						aNormalizedAdditionalProperties.push(oProperty);
					}
				}

				// Append additional properties
				return aNormalizedAdditionalProperties;
			},

			ParseHref: function(sHref) {
				return {
					Href: sHref,
					Host: ITHit.WebDAV.Client.HierarchyItem.GetHost(sHref)
				};
			},

			/**
			 * Load item from server.
			 * @private
			 * @deprecated Use asynchronous method instead
			 * @param {ITHit.WebDAV.Client.Request} oRequest Current WebDAV session.
			 * @param {string} sHref This item path on the server.
			 * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. Default is empty array.
			 * @returns {ITHit.WebDAV.Client.HierarchyItem} Loaded item.
			 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException A Folder was expected or the response doesn't have required item.
			 */
			OpenItem: function(oRequest, sHref, aProperties) {
				aProperties = aProperties || [];

				// Normalize custom properties
				aProperties = this.GetCustomRequestProperties(aProperties);

				var oHrefObject = this.ParseHref(sHref);
				var oResult = ITHit.WebDAV.Client.Methods.Propfind.Go(
					oRequest,
					oHrefObject.Href,
					ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
					[].concat(this.GetRequestProperties()).concat(aProperties),
					ITHit.WebDAV.Client.Depth.Zero,
					oHrefObject.Host
				);

				return this.GetItemFromMultiResponse(oResult.Response, oRequest, sHref, aProperties);
			},

			/**
			 * Callback function to be called when folder loaded from server.
			 * @callback ITHit.WebDAV.Client.HierarchyItem~OpenItemAsyncCallback
			 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
			 * @param {ITHit.WebDAV.Client.HierarchyItem} oResult.Result Loaded item.
			 */

			/**
			 * Load item from server.
			 * @param {ITHit.WebDAV.Client.Request} oRequest Current WebDAV session.
			 * @param {string} sHref This item path on the server.
			 * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. Default is empty array.
			 * @param {ITHit.WebDAV.Client.HierarchyItem~OpenItemAsyncCallback} fCallback Function to call when operation is completed.
			 * @returns {ITHit.WebDAV.Client.Request} Request object.
			 */
			OpenItemAsync: function(oRequest, sHref, aProperties, fCallback) {
				aProperties = aProperties || [];

				// Normalize custom properties
				aProperties = this.GetCustomRequestProperties(aProperties);

				var oHrefObject = this.ParseHref(sHref);
				ITHit.WebDAV.Client.Methods.Propfind.GoAsync(
					oRequest,
					oHrefObject.Href,
					ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
					[].concat(this.GetRequestProperties()).concat(aProperties),
					ITHit.WebDAV.Client.Depth.Zero,
					oHrefObject.Host,
					function(oAsyncResult) {
						if (oAsyncResult.IsSuccess) {
							try {
								oAsyncResult.Result = self.GetItemFromMultiResponse(oAsyncResult.Result.Response, oRequest, sHref, aProperties);
							} catch(oError) {
								oAsyncResult.Error = oError;
								oAsyncResult.IsSuccess = false;
							}
						}

						fCallback(oAsyncResult);
					}
				);

				return oRequest;
			},

			GetItemFromMultiResponse: function(oMultiResponse, oRequest, sHref, aCustomProperties) {
				aCustomProperties = aCustomProperties || [];

				// Loop through result items.
				for (var i = 0; i < oMultiResponse.Responses.length; i++) {
					var oResponse = oMultiResponse.Responses[i];

					// Whether item is found.
					if (!ITHit.WebDAV.Client.HierarchyItem.HrefEquals(oResponse.Href, sHref)) {
						continue;
					}

					return this.GetItemFromResponse(oResponse, oRequest, sHref, aCustomProperties);
				}

				throw new ITHit.WebDAV.Client.Exceptions.NotFoundException(ITHit.Phrases.FolderNotFound.Paste(sHref));
			},

			GetItemsFromMultiResponse: function (oMultiResponse, oRequest, sHref, aCustomProperties) {
				aCustomProperties = aCustomProperties || [];

				var aItems = [];

				// Loop through result items.
				for (var i = 0; i < oMultiResponse.Responses.length; i++) {
					var oResponse = oMultiResponse.Responses[i];

					// Do not include current node, get only it's child nodes.
					if (ITHit.WebDAV.Client.HierarchyItem.HrefEquals(oResponse.Href, sHref)) {
						continue;
					}

					// Ignore element whether it's status is set and not OK.
					if (oResponse.Status && !oResponse.Status.IsOk()) {
						continue;
					}

					aItems.push(this.GetItemFromResponse(oResponse, oRequest, sHref, aCustomProperties));
				}

				return aItems;
			},

			GetItemFromResponse: function(oResponse, oRequest, sHref, aCustomProperties) {
				var oHrefObject = this.ParseHref(sHref);

				// Append custom properties
				var aPropertyList = ITHit.WebDAV.Client.HierarchyItem.GetPropertiesFromResponse(oResponse);

				// Set null for not-exists properties
				for (var i2 = 0, l2 = aCustomProperties.length; i2 < l2; i2++) {
					if (!ITHit.WebDAV.Client.HierarchyItem.HasProperty(oResponse, aCustomProperties[i2])) {
						aPropertyList.push(new ITHit.WebDAV.Client.Property(aCustomProperties[i2], ''));
					}
				}

				switch (ITHit.WebDAV.Client.HierarchyItem.GetResourceType(oResponse)) {
					case ITHit.WebDAV.Client.ResourceType.File:
						return new ITHit.WebDAV.Client.File(
							oRequest.Session,
							oResponse.Href,
							ITHit.WebDAV.Client.HierarchyItem.GetLastModified(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetDisplayName(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetCreationDate(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetContentType(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetContentLength(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetSupportedLock(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetActiveLocks(oResponse, sHref),
							oHrefObject.Host,
							ITHit.WebDAV.Client.HierarchyItem.GetQuotaAvailableBytes(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetQuotaUsedBytes(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetCkeckedIn(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetCheckedOut(oResponse),
							aPropertyList
						);
						break;

					case ITHit.WebDAV.Client.ResourceType.Folder:
						return new ITHit.WebDAV.Client.Folder(
							oRequest.Session,
							oResponse.Href,
							ITHit.WebDAV.Client.HierarchyItem.GetLastModified(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetDisplayName(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetCreationDate(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetSupportedLock(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetActiveLocks(oResponse, sHref),
							oHrefObject.Host,
							ITHit.WebDAV.Client.HierarchyItem.GetQuotaAvailableBytes(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetQuotaUsedBytes(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetCkeckedIn(oResponse),
							ITHit.WebDAV.Client.HierarchyItem.GetCheckedOut(oResponse),
							aPropertyList
						);

					default:
						throw new ITHit.WebDAV.Client.Exceptions.WebDavException(ITHit.Phrases.Exceptions.UnknownResourceType);
				}
			},

			/**
			 * Get item's full path.
			 * @param {string} sUri Base URI.
			 * @param {string} sDestinationName Item name.
			 * @returns {string} Item full path.
			 */
			AppendToUri: function(sUri, sDestinationName) {
				return ITHit.WebDAV.Client.HierarchyItem.GetAbsoluteUriPath(sUri) + ITHit.WebDAV.Client.Encoder.EncodeURI(sDestinationName);
			},

			/**
			 * Retrieves locks for this item.
			 * @returns {ITHit.WebDAV.Client.LockInfo[]} List of LockInfo objects.
			 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
			 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
			 */
			GetActiveLocks: function(oResp, sHref){

				// Get lock name.
				var oLockDiscovery = ITHit.WebDAV.Client.DavConstants.LockDiscovery.toString();


				for (var i = 0; i < oResp.Propstats.length; i++) {
					var oPropstat = oResp.Propstats[i];

					if (!oPropstat.Status.IsOk()) {
						break;
					}

					if ('undefined' != typeof oPropstat.PropertiesByNames[oLockDiscovery]) {
						var oProp = oPropstat.PropertiesByNames[oLockDiscovery];

						try {
							// Return active locks.
							return ITHit.WebDAV.Client.LockInfo.ParseLockDiscovery(oProp.Value, sHref);
						} catch (e) {
							if (typeof window.console !== 'undefined') {
								console.error(e.stack || e.toString());
							}
							break;
						}

					} else {
						break;
					}
				}

				return [];
			},

			/**
			 * Retrieves locks for this item.
			 * @returns {Array} Supported locks.
			 */
			GetSupportedLock: function(oResp) {

				var oSupportedLock = ITHit.WebDAV.Client.DavConstants.SupportedLock;

				for (var i = 0; i < oResp.Propstats.length; i++ ) {
					var oPropstat = oResp.Propstats[i];

					if (!oPropstat.Status.IsOk()) {
						break;
					}

					var out = [];
					for (var p in oPropstat.PropertiesByNames) {
						out.push(p);
					}

					if ('undefined' != typeof oPropstat.PropertiesByNames[oSupportedLock]) {
						var oProp = oPropstat.PropertiesByNames[oSupportedLock];
						try {
							return ITHit.WebDAV.Client.HierarchyItem.ParseSupportedLock(oProp.Value);
						} catch (e) {
							break;
						}
					}
				}

				return [];
			},

			/**
			 * Parse supported locks.
			 * @param {ITHit.XMLDoc} oSupportedLockProp XML DOM lock property element.
			 * @returns {Array} Supported locks.
			 */
			ParseSupportedLock: function(oSupportedLockProp) {

				var aLocks = [];

				// Create namespace resolver.
				var oResolver = new ITHit.XPath.resolver();
				oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);

				var oNode       = null;
				var oNode1      = null;
				var iNodeElType = ITHit.XMLDoc.nodeTypes.NODE_ELEMENT;

				var oRes  = ITHit.XPath.evaluate('d:lockentry', oSupportedLockProp, oResolver);
				while ( oNode = oRes.iterateNext() ) {

					var oRes1     = ITHit.XPath.evaluate('d:*', oNode, oResolver);
					while (oNode1 = oRes1.iterateNext()) {

						if (oNode1.nodeType() == iNodeElType) {

							var sNodeName = '';

							if (oNode1.hasChildNodes()) {

								var oChildNode = oNode1.firstChild();
								while (oChildNode) {
									if (oChildNode.nodeType() == iNodeElType) {
										sNodeName = oChildNode.localName();
										break;
									}
									oChildNode = oChildNode.nextSibling();
								}
							}
							else {
								sNodeName = oNode1.localName();
							}

							switch (sNodeName.toLowerCase()) {

								case 'shared':
									aLocks.push(ITHit.WebDAV.Client.LockScope.Shared);
									break;

								case 'exclusive':
									aLocks.push(ITHit.WebDAV.Client.LockScope.Exclusive);
									break;
							}
						}
					}
				}

				return aLocks;
			},

			/**
			 * Retrieves information about quota available bytes.
			 * @returns {number} Available bytes.
			 */
			GetQuotaAvailableBytes: function(oResp) {

				var oAvailableBytes = ITHit.WebDAV.Client.DavConstants.QuotaAvailableBytes;

				for (var i = 0; i < oResp.Propstats.length; i++ ) {
					var oPropstat = oResp.Propstats[i];

					if (!oPropstat.Status.IsOk()) {
						break;
					}

					if ('undefined' != typeof oPropstat.PropertiesByNames[oAvailableBytes]) {
						var oProp = oPropstat.PropertiesByNames[oAvailableBytes];
						try {
							return parseInt(oProp.Value.firstChild().nodeValue());
						} catch (e) {
							break;
						}
					}
				}

				return -1;
			},

			/**
			 * Retrieves information about quota used bytes.
			 * @returns {number} Used bytes.
			 */
			GetQuotaUsedBytes: function(oResp) {

				var oUsedBytes = ITHit.WebDAV.Client.DavConstants.QuotaUsedBytes;

				for (var i = 0; i < oResp.Propstats.length; i++ ) {
					var oPropstat = oResp.Propstats[i];

					if (!oPropstat.Status.IsOk()) {
						break;
					}

					if ('undefined' != typeof oPropstat.PropertiesByNames[oUsedBytes]) {
						var oProp = oPropstat.PropertiesByNames[oUsedBytes];
						try {
							return parseInt(oProp.Value.firstChild().nodeValue());
						} catch (e) {
							break;
						}
					}
				}

				return -1;
			},

			/**
			 * Retrieves information about checked-in item.
			 * @returns {Array|boolean} Array checked-in files or false, if versions is not supported
			 */
			GetCkeckedIn: function(oResp) {

				var CheckedIn = ITHit.WebDAV.Client.DavConstants.CheckedIn;

				for (var i = 0; i < oResp.Propstats.length; i++ ) {
					var oPropstat = oResp.Propstats[i];

					if (!oPropstat.Status.IsOk()) {
						break;
					}

					if ('undefined' != typeof oPropstat.PropertiesByNames[CheckedIn]) {
						var oProp = oPropstat.PropertiesByNames[CheckedIn];
						try {
							return ITHit.WebDAV.Client.HierarchyItem.ParseChecked(oProp.Value);
						} catch (e) {
							break;
						}
					}
				}

				return false;
			},

			/**
			 * Retrieves information about checked-out item.
			 * @returns {number} Used bytes.
			 */
			GetCheckedOut: function(oResp) {

				var CheckedIn = ITHit.WebDAV.Client.DavConstants.CheckedOut;

				for (var i = 0; i < oResp.Propstats.length; i++ ) {
					var oPropstat = oResp.Propstats[i];

					if (!oPropstat.Status.IsOk()) {
						break;
					}

					if ('undefined' != typeof oPropstat.PropertiesByNames[CheckedIn]) {
						var oProp = oPropstat.PropertiesByNames[CheckedIn];
						try {
							return ITHit.WebDAV.Client.HierarchyItem.ParseChecked(oProp.Value);
						} catch (e) {
							break;
						}
					}
				}

				return false;
			},

			/**
			 * Parse checked-in/out files.
			 * @param {ITHit.XMLDoc} oCheckedProp XML DOM lock property element.
			 * @returns {Array} Checked files.
			 */
			ParseChecked: function(oCheckedProp) {

				var aCheckeds = [];

				// Create namespace resolver.
				var oResolver = new ITHit.XPath.resolver();
				oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);

				var oNode       = null;
				var iNodeElType = ITHit.XMLDoc.nodeTypes.NODE_ELEMENT;

				var oRes  = ITHit.XPath.evaluate('d:href', oCheckedProp, oResolver);
				while ( oNode = oRes.iterateNext() ) {
					if (oNode.nodeType() == iNodeElType) {
						aCheckeds.push(oNode.firstChild().nodeValue());
					}
				}

				return aCheckeds;
			},

			/**
			 * Get resource type.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @returns {string} Resource type.
			 */
			GetResourceType: function(oResponse) {

				var oProperty = ITHit.WebDAV.Client.HierarchyItem.GetProperty(oResponse, ITHit.WebDAV.Client.DavConstants.ResourceType);
				var sResourceType = ITHit.WebDAV.Client.ResourceType.File;

				if (oProperty.Value.getElementsByTagNameNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'collection').length > 0) {
					sResourceType = ITHit.WebDAV.Client.ResourceType.Folder;
				}

				return sResourceType;
			},

			/**
			 * Has property.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @param {ITHit.WebDAV.Client.PropertyName} oPropName Property name.
			 * @returns {boolean} Searched property exits.
			 */
			HasProperty: function(oResponse, oPropName) {

				for ( var i = 0; i < oResponse.Propstats.length; i++ ) {
					var oPropstat = oResponse.Propstats[i];
					for ( var j = 0; j < oPropstat.Properties.length; j++ ) {
						var oProperty = oPropstat.Properties[j];
						if (oProperty.Name.Equals(oPropName)) {
							return true;
						}
					}
				}

				return false;
			},

			/**
			 * Get property.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @param {ITHit.WebDAV.Client.PropertyName} oPropName Property name.
			 * @returns {ITHit.WebDAV.Client.Property} Searched property.
			 * @throws ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException Property was not found.
			 */
			GetProperty: function(oResponse, oPropName) {

				for ( var i = 0; i < oResponse.Propstats.length; i++ ) {
					var oPropstat = oResponse.Propstats[i];
					for ( var j = 0; j < oPropstat.Properties.length; j++ ) {
						var oProperty = oPropstat.Properties[j];
						if (oProperty.Name.Equals(oPropName)) {
							return oProperty;
						}
					}
				}

				throw new ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException(ITHit.Phrases.Exceptions.PropertyNotFound, oResponse.Href, oPropName, null, null);
			},

			/**
			 * Get custom properties key-value object.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @returns {ITHit.WebDAV.Client.Property[]} Custom properties.
			 */
			GetPropertiesFromResponse: function(oResponse) {
				var aProperties = [];

				for ( var i = 0; i < oResponse.Propstats.length; i++ ) {
					var oPropstat = oResponse.Propstats[i];
					for ( var i2 = 0; i2 < oPropstat.Properties.length; i2++ ) {
						aProperties.push(oPropstat.Properties[i2]);
					}
				}

				return aProperties;
			},

			/**
			 * Get item's name.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @returns {string} Item's name.
			 */
			GetDisplayName: function(oResponse) {

				var oElement = ITHit.WebDAV.Client.HierarchyItem.GetProperty(oResponse,  ITHit.WebDAV.Client.DavConstants.DisplayName).Value;
				var sName;

				if (oElement.hasChildNodes()) {
					sName = oElement.firstChild().nodeValue();
				} else {
					sName = ITHit.WebDAV.Client.Encoder.Decode(ITHit.WebDAV.Client.HierarchyItem.GetLastName(oResponse.Href));
				}

				return sName;
			},

			/**
			 * Get item's last modified date.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @returns {Date} Item's last modified date.
			 */
			GetLastModified: function(oResponse) {
                var oProp;
                try {
				    oProp = ITHit.WebDAV.Client.HierarchyItem.GetProperty(oResponse, ITHit.WebDAV.Client.DavConstants.GetLastModified);
                } catch (e) {
                    if (!(e instanceof ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException)) {
                        throw e;
                    }
                    return null;
                }

				return ITHit.WebDAV.Client.HierarchyItem.GetDate(oProp.Value.firstChild().nodeValue(), 'rfc1123');
			},

			/**
			 * Get item's content type.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @returns {string} Item's content type.
			 */
			GetContentType: function(oResponse) {

				var sContentType = null;
				var oValue = ITHit.WebDAV.Client.HierarchyItem.GetProperty(oResponse, ITHit.WebDAV.Client.DavConstants.GetContentType).Value;
				if (oValue.hasChildNodes()) {
					sContentType = oValue.firstChild().nodeValue();
				}
				return sContentType;
			},

			/**
			 * Get file content length.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @returns {number|null} Content length.
			 */
			GetContentLength: function(oResponse) {

				var iContentLength = 0;
                try {
                    var oValue = ITHit.WebDAV.Client.HierarchyItem.GetProperty(oResponse, ITHit.WebDAV.Client.DavConstants.GetContentLength).Value;
                    if (oValue.hasChildNodes()) {
                        iContentLength = parseInt(oValue.firstChild().nodeValue());
                    }
                } catch (e) {
                    if (!(e instanceof ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException)) {
                        throw e;
                    }
                    return null;
                }
				return iContentLength;
			},

			/**
			 * Get item's creating date.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @returns {Date} Item's creation date.
			 */
			GetCreationDate: function(oResponse) {
                var oProp;
                try {
                    oProp = ITHit.WebDAV.Client.HierarchyItem.GetProperty(oResponse, ITHit.WebDAV.Client.DavConstants.CreationDate);
                } catch (e) {
                    if (!(e instanceof ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException)) {
                        throw e;
                    }
                    return null;
                }

				return ITHit.WebDAV.Client.HierarchyItem.GetDate(oProp.Value.firstChild().nodeValue(), 'tz');
			},

			GetDate: function(sDate, sDateFormat) {

				var oDate;
				var i = 0; // rfc1123

				if ('tz' == sDateFormat) {
					i++; // tz
				}

				if (!sDate) {
					return new Date(0);
				}

				for (var e = i + 1; i <= e; i++) {

					if (0 == i % 2) {

						// rfc1123
						var oDate = new Date(sDate);

						if (!isNaN(oDate)) {
							break;
						}
					}
					else {

						// tz
						var aTime = sDate.match(/([\d]{4})\-([\d]{2})\-([\d]{2})T([\d]{2}):([\d]{2}):([\d]{2})(\.[\d]+)?((?:Z)|(?:[\+\-][\d]{2}:[\d]{2}))/);

						if (aTime && aTime.length >= 7) {

							aTime.shift();

							var oDate = new Date(aTime[0], aTime[1] - 1, aTime[2], aTime[3], aTime[4], aTime[5]);

							var iCounter = 6;
							if (('undefined' != typeof aTime[iCounter]) && (-1 != aTime[iCounter].indexOf('.'))) {
								oDate.setMilliseconds(aTime[iCounter].replace(/[^\d]/g, ''));
							}
							iCounter++;

							if (('undefined' != typeof aTime[iCounter]) && ('-00:00' != aTime[iCounter]) && (-1 != aTime[iCounter].search(/(?:\+|-)/))) {

								var aParts = aTime[iCounter].slice(1).split(':');
								var iOffset = parseInt(aParts[1]) + (60 * aParts[0]);

								if ('+' == aTime[iCounter][0]) {
									oDate.setMinutes(oDate.getMinutes() - iOffset);
								}
								else {
									oDate.setMinutes(oDate.getMinutes() + iOffset);
								}

								iCounter++;
							}

							oDate.setMinutes(oDate.getMinutes() + (-1 * oDate.getTimezoneOffset()));

							break;
						}
					}
				}

				if (!oDate || isNaN(oDate)) {
					oDate = new Date(0);
				}

				return oDate;

			},

			/**
			 * Get folder's absolute path.
			 * @param {string} sHref Folder's URL.
			 * @returns {string} Folder's URL.
			 */
			GetAbsoluteUriPath: function(sHref) {
				return sHref.replace(/\/?$/, '/');
			},

			/**
			 * Get path without host.
			 * @param {string} sHref Folder's URL.
			 * @return {string} Folder's URL.
			 */
			GetRelativePath: function(sHref) {
				return sHref.replace(/^[a-z]+\:\/\/[^\/]+\//, '\/');
			},

			GetLastName: function(sHref) {

				// Get relative path.
				var sName = ITHit.WebDAV.Client.HierarchyItem.GetRelativePath(sHref).replace(/\/$/, '');

				return sName.match(/[^\/]*$/)[0];
			},

			/**
			 * Check whether hrefs are equals.
			 * @param {string} sHref1 URL 1.
			 * @param {string} sHref2 URL 2.
			 * @returns {boolean} True if URLs are equals, false otherwise.
			 */
			HrefEquals: function(sHref1, sHref2) {

				// TODO: Uncomment when encoding special characters on server will be fixed.
				//	var iPos         = sHref1.indexOf('?');
				//	if (-1 != iPos) {
				//		sHref1 = sHref1.substr(0, iPos);
				//	}
				//	var iPos         = sHref1.indexOf('#');
				//	if (-1 != iPos) {
				//		sHref1 = sHref1.substr(0, iPos);
				//	}

				//	var iPos         = sHref2.indexOf('?');
				var iPos         = sHref2.search(/\?[^\/]+$/);
				if (-1 != iPos) {
					sHref2 = sHref2.substr(0, iPos);
				}
				//	var iPos         = sHref2.indexOf('#');
				var iPos         = sHref2.search(/\?[^\/]+$/);
				if (-1 != iPos) {
					sHref2 = sHref2.substr(0, iPos);
				}

				return ITHit.WebDAV.Client.HierarchyItem.GetRelativePath(ITHit.WebDAV.Client.Encoder.Decode(sHref1)).replace(/\/$/, '') == ITHit.WebDAV.Client.HierarchyItem.GetRelativePath(ITHit.WebDAV.Client.Encoder.Decode(sHref2)).replace(/\/$/, '');
			},

			/**
			 * Get folder parent path.
			 * @param {string} sHref Folder URL.
			 * @returns {string} Folder parent URL.
			 */
			GetFolderParentUri: function(sHref) {

				// Get parent folder URI.
				var sHost = /^https?\:\/\//.test(sHref) ? sHref.match(/^https?\:\/\/[^\/]+/)[0] + '/' : '/';
				var sPath = ITHit.WebDAV.Client.HierarchyItem.GetRelativePath(sHref);
				sPath = sPath.replace(/\/?$/, '');

				if (sPath === '') {
					return null;
				}

				sPath = sPath.substr(0, sPath.lastIndexOf('/') + 1);
				sPath = sPath.substr(1);

				return sHost + sPath;
			},

			/**
			 * Get host from URL.
			 * @param {string} sHref Item's URL.
			 * @returns {string} Server host.
			 */
			GetHost: function(sHref) {

				var sHost;

				if (/^https?\:\/\//.test(sHref)) {
					sHost = sHref.match(/^https?\:\/\/[^\/]+/)[0] + '/';
				}
				else {
					sHost = location.protocol +'//'+ location.host +'/';
				}

				return sHost;
			},

			GetPropertyValuesFromMultiResponse: function(oMultiResponses, sHref) {

				for (var i = 0; i < oMultiResponses.Responses.length; i++) {
					var oResponse = oMultiResponses.Responses[i];

					if (!ITHit.WebDAV.Client.HierarchyItem.HrefEquals(oResponse.Href, sHref)) {
						continue;
					}

					var oProperties = [];
					for (var j = 0; j < oResponse.Propstats.length; j++) {
						var oPropstat = oResponse.Propstats[j];
						if (!oPropstat.Properties.length) {
							continue;
						}

						// Success
						if (oPropstat.Status.IsSuccess()) {

							for (var k = 0; k < oPropstat.Properties.length; k++) {
								var oProperty = oPropstat.Properties[k];

								// Add only custom properties.
								if (!oProperty.Name.IsStandardProperty()) {
									oProperties.push(oProperty);
								}
							}
							continue;
						}

						if (oPropstat.Status.Equals(ITHit.WebDAV.Client.HttpStatus.NotFound)) {
							throw new ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException(ITHit.Phrases.Exceptions.PropertyNotFound, sHref, oPropstat.Properties[0].Name, new ITHit.WebDAV.Client.Exceptions.Info.PropertyMultistatus(oMultiResponses), null);
						}

						if (oPropstat.Status.Equals(ITHit.WebDAV.Client.HttpStatus.Forbidden)) {
							throw new ITHit.WebDAV.Client.Exceptions.PropertyForbiddenException(ITHit.Phrases.Exceptions.PropertyForbidden, sHref, oPropstat.Properties[0].Name, new ITHit.WebDAV.Client.Exceptions.Info.PropertyMultistatus(oMultiResponses), null);
						}

						throw new ITHit.WebDAV.Client.Exceptions.PropertyException(ITHit.Phrases.Exceptions.PropertyFailed, sHref, oPropstat.Properties[0].Name, new ITHit.WebDAV.Client.Exceptions.Info.PropertyMultistatus(oMultiResponses), oPropstat.Status, null);
					}
					return oProperties;
				}

				throw new ITHit.WebDAV.Client.Exceptions.WebDavException(ITHit.Phrases.ResponseItemNotFound.Paste(sHref));
			},

			GetPropertyNamesFromMultiResponse: function(oMultiResponses, sHref) {

				var oPropertyNames = [];
				var oProperties = this.GetPropertyValuesFromMultiResponse(oMultiResponses, sHref);
				for (var i = 0, l = oProperties.length; i < l; i++) {
					oPropertyNames.push(oProperties[i].Name);
				}

				return oPropertyNames;
			},

			GetSourceFromMultiResponse: function(oResponses, sHref) {

				for (var i = 0; i < oResponses.length; i++) {
					var oResponse = oResponses[i];

					if (!ITHit.WebDAV.Client.HierarchyItem.HrefEquals(oResponse.Href, sHref)) {
						continue;
					}

					var oSources = []
					for (var j = 0; j < oResponse.Propstats; j++) {
						var oPropstat = oResponse.Propstats[j];

						if (!oPropstat.Status.IsOk()) {
							if (oPropstat.Status.Equals(ITHit.WebDAV.Client.HttpStatus.NotFound)) {
								return null;
							}

							throw new ITHit.WebDAV.Client.Exceptions.PropertyForbiddenException(
								ITHit.Phrases.PropfindFailedWithStatus.Paste(oPropstat.Status.Description),
								sHref,
								oPropstat.Properties[0].Name,
								new ITHit.WebDAV.Client.Exceptions.Info.Multistatus(oResponse)
							);
						}

						for (var k = 0; k < oPropstat.Properties.length; k++) {
							var oProperty = oPropstat.Properties[k];

							if (oProperty.Name.Equals(ITHit.WebDAV.Client.DavConstants.Source)) {
								var aLinks = oProperty.Value.GetElementsByTagNameNS(DavConstants.NamespaceUri, DavConstants.Link);
								for (var l = 0; l < aLinks.length; l++) {
									var oLink = aLinks[i];
									var oSource = new ITHit.WebDAV.Client.Source(
										oLink.GetElementsByTagName(ITHit.WebDAV.Client.DavConstants.NamespaceUri, ITHit.WebDAV.Client.DavConstants.Src)[0].firstChild().nodeValue(),
										oLink.GetElementsByTagName(ITHit.WebDAV.Client.DavConstants.NamespaceUri, ITHit.WebDAV.Client.DavConstants.Dst)[0].firstChild().nodeValue()
									);
									oSources.push(oSource);
								}

								return oSources;
							}
						}
					}
				}

				throw new ITHit.WebDAV.Client.Exceptions.WebDavException(ITHit.Phrases.ResponseItemNotFound.Paste(sHref));
			}		    

		},

		/**
		 * Current WebDAV session.
		 * @api
		 * @type {ITHit.WebDAV.Client.WebDavSession}
		 */
		Session: null,

		/**
		 * This item path on the server.
		 * @api
		 * @type {string}
		 */
		Href: null,

		/**
		 * Most recent modification date.
		 * @api
		 * @type {Date}
		 */
		LastModified: null,

		/**
		 * User friendly item name.
		 * @api
		 * @type {string}
		 */
		DisplayName: null,

		/**
		 * The date item was created.
		 * @api
		 * @type {Date}
		 */
		CreationDate: null,

		/**
		 * Type of the item (File or Folder).
		 * @api
		 * @type {string}
		 * @see ITHit.WebDAV.Client.ResourceType
		 */
		ResourceType: null,

		/**
		 * Retrieves information about supported locks. Item can support exclusive, shared locks or do not support
		 * any locks. If you set exclusive lock other users will not be able to set any locks. If you set shared
		 * lock other users will be able to set shared lock on the item.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.Locks.CheckSupport.CheckLockSupport
		 * @type {Array}
		 * @see ITHit.WebDAV.Client.LockScope
		 */
		SupportedLocks: null,

		/**
		 * List of locks applied to this item.
		 * @examplecode ITHit.WebDAV.Client.Tests.Locks.GetLocks.GetList
		 * @api
		 * @type {Array}
		 */
		ActiveLocks: null,

		/**
		 * List of item properties.
		 * @api
		 * @type {ITHit.WebDAV.Client.PropertyList}
		 */
		Properties: null,

		/**
		 * Returns true if file is under version control. Otherwise false. To detect if version control could
		 * be enabled for this item call GetSupportedFeaturesAsync and check for VersionControl token.
		 * To enable version control call PutUnderVersionControlAsync.
		 * @api
		 * @returns {boolean} Boolean, if true - versions supported
		 */
		VersionControlled: null,

		/**
		 * Server host.
		 * @type {string}
		 */
		Host: null,

		/**
		 * Number of bytes available for this user on server. -1 if server does not support Quota.
		 * @api
		 * @type {number}
		 */
		AvailableBytes: null,

		/**
		 * Number of bytes used by this user on server. -1 if server does not support Quota.
		 * @api
		 * @type {number}
		 */
		UsedBytes: null,

		/**
		 * Checked-in files list
		 * @type {Array|boolean}
		 */
		CheckedIn: null,

		/**
		 * Checked-in files list
		 * @type {Array|boolean}
		 */
		CheckedOut: null,

		/**
		 * Server version (engine header)
		 * @type {Array}
		 */
		ServerVersion: null,

		/**
		 * @type {string}
		 */
		_Url: null,

		/**
		 * @type {string}
		 */
		_AbsoluteUrl: null,

		/**
		 * Create new instance of HierarchyItem class which represents one WebDAV item (file, folder or lock-null).
		 * @param {ITHit.WebDAV.Client.WebDavSession} oSession Current WebDAV session
		 * @param {string} sHref This item path on the server.
		 * @param {Date} oLastModified Most recent modification date.
		 * @param {string} sDisplayName User friendly item name.
		 * @param {Date} oCreationDate The date item was created.
		 * @param {string} sResourceType Type of this item, see ResourceType.
		 * @param {Array} aSupportedLocks
		 * @param {Array} aActiveLocks
		 * @param {string} sHost
		 * @param {number} iAvailableBytes
		 * @param {number} iUsedBytes
		 * @param {Array|boolean} aCheckedIn
		 * @param {Array|boolean} aCheckedOut
		 * @param {object} aProperties
		 */
		constructor: function(oSession, sHref, oLastModified, sDisplayName, oCreationDate, sResourceType, aSupportedLocks, aActiveLocks, sHost, iAvailableBytes, iUsedBytes, aCheckedIn, aCheckedOut, aProperties) {
			this.Session = oSession;
			this.ServerVersion = oSession.ServerEngine;
			this.Href = sHref;
			this.LastModified = oLastModified;
			this.DisplayName = sDisplayName;
			this.CreationDate = oCreationDate;
			this.ResourceType = sResourceType;
			this.SupportedLocks = aSupportedLocks;
			this.ActiveLocks = aActiveLocks;
			this.Host = sHost;
			this.AvailableBytes = iAvailableBytes;
			this.UsedBytes = iUsedBytes;
			this.CheckedIn = aCheckedIn;
			this.CheckedOut = aCheckedOut;
			this.Properties = new ITHit.WebDAV.Client.PropertyList();
			this.Properties.push.apply(this.Properties, aProperties || []);

			this.VersionControlled = this.CheckedIn !== false || this.CheckedOut !== false;

			// Add shortcuts, used in AjaxFileBrowser
			this._AbsoluteUrl = ITHit.Decode(this.Href);
			this._Url = this._AbsoluteUrl.replace(/^http[s]?:\/\/[^\/]+\/?/, '\/');
		},

		/**
		 *
		 * @returns {boolean}
		 */
		IsFolder: function() {
			return false;
		},

		/**
		 * @param {string|ITHit.WebDAV.Client.HierarchyItem} mItem is absolute/relative url or HierarchyItem instance
		 * @returns {boolean}
		 */
		IsEqual: function(mItem) {
			if (mItem instanceof ITHit.WebDAV.Client.HierarchyItem) {
				return this.Href === mItem.Href;
			}

			if (ITHit.Utils.IsString(mItem)) {
				if (mItem.indexOf('://') !== -1 || mItem.indexOf(':\\') !== -1) {
					return this.GetAbsoluteUrl() === mItem;
				}

				return this.GetUrl() === mItem;
			}

			return false;
		},

		/**
		 * @returns {string}
		 */
		GetUrl: function() {
			return this._Url;
		},

		/**
		 * @returns {string}
		 */
		GetAbsoluteUrl: function() {
			return this._AbsoluteUrl;
		},

		/**
		 * Check to property exists
		 * @private
		 * @deprecated Use Properties.Has() for check property exists
		 * @param {ITHit.WebDAV.Client.PropertyName} oPropName Property name.
		 * @returns {boolean}
		 */
		HasProperty: function(oPropName) {
			for (var i = 0, l = this.Properties.length; i < l; i++) {
				if (oPropName.Equals(this.Properties[i].Name)) {
					return true;
				}
			}
			return false;
		},

		/**
		 * Get additional property
		 * @private
		 * @deprecated Use Properties.Find() for get property value
		 * @param {ITHit.WebDAV.Client.PropertyName} oPropName Property name.
		 * @returns {*}
		 */
		GetProperty: function(oPropName) {
			for (var i = 0, l = this.Properties.length; i < l; i++) {
				if (oPropName.Equals(this.Properties[i].Name)) {
					return this.Properties[i].Value.firstChild().nodeValue();
				}
			}

			throw new ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException('Not found property `' + oPropName.toString() + '` in resource `' + this.Href + '`.');
		},

		/**
		 * Refreshes item loading data from server.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @throws ITHit.WebDAV.Client.Exceptions.UnauthorizedException Incorrect credentials provided or insufficient permissions to access the requested item.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException The requested folder doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException The server refused to fulfill the request.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		Refresh: function() {
			var oRequest = this.Session.CreateRequest(this.__className + '.Refresh()');

			var aProperties = [];
			for (var i = 0, l = this.Properties.length; i < l; i++) {
				aProperties.push(this.Properties[i].Name);
			}

			var oItem = self.OpenItem(oRequest, this.Href, aProperties);
			for (var key in oItem) {
				if (oItem.hasOwnProperty(key)) {
					this[key] = oItem[key];
				}
			}

			oRequest.MarkFinish();
		},

		/**
		 * Callback function to be called when item data loaded from server and item is refreshed.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~RefreshAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Refreshes item loading data from server.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.Refresh.Refresh
		 * @param {ITHit.WebDAV.Client.HierarchyItem~RefreshAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		RefreshAsync: function(fCallback) {
			var that = this;
			var oRequest = this.Session.CreateRequest(this.__className + '.RefreshAsync()');

			var aProperties = [];
			for (var i = 0, l = this.Properties.length; i < l; i++) {
				aProperties.push(this.Properties[i].Name);
			}

			self.OpenItemAsync(oRequest, this.Href, aProperties, function(oAsyncResult) {
				if (oAsyncResult.IsSuccess) {
					for (var key in oAsyncResult.Result) {
						if (oAsyncResult.Result.hasOwnProperty(key)) {
							that[key] = oAsyncResult.Result[key];
						}
					}
					oAsyncResult.Result = null;
				}

				oRequest.MarkFinish();
				fCallback(oAsyncResult);
			});

			return oRequest;
		},

		/**
		 * Copies this item to destination folder.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {ITHit.WebDAV.Client.Folder} oDestinationFolder Folder to move to.
		 * @param {string} sDestinationName Name to assign to copied item.
		 * @param {boolean} bDeep Indicates whether children of this item should be copied.
		 * @param {boolean} bOverwrite Whether existing destination item shall be overwritten.
		 * @param {ITHit.WebDAV.Client.LockUriTokenPair[]} [oLockTokens] Lock tokens for destination folder.
		 * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException The source and destination URIs are the same.
		 * @throws ITHit.WebDAV.Client.Exceptions.LockedException The destination folder or items to be overwritten were locked.
		 * @throws ITHit.WebDAV.Client.Exceptions.PreconditionFailedException The destination item exists and overwrite was false.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error for specific resource.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		CopyTo: function(oDestinationFolder, sDestinationName, bDeep, bOverwrite, oLockTokens) {
			oLockTokens = oLockTokens || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.CopyTo()');

			var oResult = ITHit.WebDAV.Client.Methods.CopyMove.Go(
				oRequest,
				ITHit.WebDAV.Client.Methods.CopyMove.Mode.Copy,
				this.Href,
				ITHit.WebDAV.Client.HierarchyItem.AppendToUri(oDestinationFolder.Href, sDestinationName),
				this.ResourceType === ITHit.WebDAV.Client.ResourceType.Folder,
				bDeep,
				bOverwrite,
				oLockTokens,
				this.Host
			);

			var oError = this._GetErrorFromCopyResponse(oResult.Response);
			if (oError) {
				oRequest.MarkFinish();
				throw oError;
			}

			oRequest.MarkFinish();
		},

		/**
		 * Callback function to be called when copy operation is complete on server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~CopyToAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Copies this item to destination folder.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.CopyMove.Copy
		 * @param {ITHit.WebDAV.Client.Folder} oDestinationFolder Folder to move to.
		 * @param {string} sDestinationName Name to assign to copied item.
		 * @param {boolean} bDeep Indicates whether children of this item should be copied.
		 * @param {boolean} bOverwrite Whether existing destination item shall be overwritten.
		 * @param {ITHit.WebDAV.Client.LockUriTokenPair[]} [oLockTokens] Lock tokens for destination folder.
		 * @param {ITHit.WebDAV.Client.HierarchyItem~CopyToAsyncCallback} fCallback Function to call when operation is completed.
		 */
		CopyToAsync: function(oDestinationFolder, sDestinationName, bDeep, bOverwrite, oLockTokens, fCallback) {
			oLockTokens = oLockTokens || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.CopyToAsync()');

			var that = this;
			ITHit.WebDAV.Client.Methods.CopyMove.GoAsync(
				oRequest,
				ITHit.WebDAV.Client.Methods.CopyMove.Mode.Copy,
				this.Href,
				ITHit.WebDAV.Client.HierarchyItem.AppendToUri(oDestinationFolder.Href, sDestinationName),
				(this.ResourceType == ITHit.WebDAV.Client.ResourceType.Folder),
				bDeep,
				bOverwrite,
				oLockTokens,
				this.Host,
				function (oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						oAsyncResult.Error = that._GetErrorFromCopyResponse(oAsyncResult.Result.Response);
						if (oAsyncResult.Error !== null) {
							oAsyncResult.IsSuccess = false;
							oAsyncResult.Result = null;
						}
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		/**
		 * Deletes this item.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {ITHit.WebDAV.Client.LockUriTokenPair} [oLockTokens] Lock tokens for this item or any locked child item.
		 * @throws ITHit.WebDAV.Client.Exceptions.LockedException This folder or any child item is locked and no or invalid lock token was specified.
		 * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException User has not enough rights to perform this operation.
		 * @throws ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException Trying to delete lock-null item. Lock-null items must be deleted using Unlock method.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		Delete: function(oLockTokens) {
			oLockTokens = oLockTokens || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.Delete()');

			var oResult = ITHit.WebDAV.Client.Methods.Delete.Go(oRequest, this.Href, oLockTokens, this.Host);

			var oError = this._GetErrorFromDeleteResponse(oResult.Response);
			if (oError) {
				oRequest.MarkFinish();
				throw oError;
			}

			oRequest.MarkFinish();
		},

		/**
		 * Callback function to be called when delete operation is complete on server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~DeleteAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Deletes this item.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.Delete.Delete
		 * @param {ITHit.WebDAV.Client.LockUriTokenPair} oLockTokens Lock tokens for this item or any locked child item.
		 * @param {ITHit.WebDAV.Client.HierarchyItem~DeleteAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		DeleteAsync: function(oLockTokens, fCallback) {
			oLockTokens = oLockTokens || null;
            fCallback = fCallback || function(){};

			var oRequest = this.Session.CreateRequest(this.__className + '.DeleteAsync()');

			var that = this;
			ITHit.WebDAV.Client.Methods.Delete.GoAsync(oRequest, this.Href, oLockTokens, this.Host, function(oAsyncResult) {
				if (oAsyncResult.IsSuccess) {
					oAsyncResult.Error = that._GetErrorFromDeleteResponse(oAsyncResult.Result.Response);
					if (oAsyncResult.Error !== null) {
						oAsyncResult.IsSuccess = false;
						oAsyncResult.Result = null;
					}
				}

				oRequest.MarkFinish();
				fCallback(oAsyncResult);
			});

			return oRequest;
		},

		/**
		 * Returns names of all custom properties exposed by this item.
		 * @private
		 * @returns {ITHit.WebDAV.Client.PropertyName[]} List of PropertyName objects.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		GetPropertyNames: function() {

			var oRequest = this.Session.CreateRequest(this.__className + '.GetPropertyNames()');

			var oResult = ITHit.WebDAV.Client.Methods.Propfind.Go(
				oRequest,
				this.Href,
				ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.PropertyNames,
				null,
				ITHit.WebDAV.Client.Depth.Zero,
				this.Host
			);

			var oPropertyName = self.GetPropertyNamesFromMultiResponse(oResult.Response, this.Href);

			oRequest.MarkFinish();
			return oPropertyName;
		},

		/**
		 * Callback function to be called when property names loaded from server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~GetPropertyNamesAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 * @param {ITHit.WebDAV.Client.PropertyName[]} oResult.Result List of PropertyName objects.
		 */

		/**
		 * Returns names of all custom properties exposed by this item.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyProperties.GetProperties.GetPropertyNames
		 * @param {ITHit.WebDAV.Client.HierarchyItem~GetPropertyNamesAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		GetPropertyNamesAsync: function(fCallback) {

			var oRequest = this.Session.CreateRequest(this.__className + '.GetPropertyNamesAsync()');

			var that = this;
			ITHit.WebDAV.Client.Methods.Propfind.GoAsync(
				oRequest,
				this.Href,
				ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.PropertyNames,
				null,
				ITHit.WebDAV.Client.Depth.Zero,
				this.Host,
				function(oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						try {
							oAsyncResult.Result = self.GetPropertyNamesFromMultiResponse(oAsyncResult.Result.Response, that.Href);
						} catch(oError) {
							oAsyncResult.Error = oError;
							oAsyncResult.IsSuccess = false;
						}
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		/**
		 * Retrieves values of specific properties.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {ITHit.WebDAV.Client.PropertyName[]} [aNames] Array of requested properties with values.
		 * @returns {ITHit.WebDAV.Client.Property[]} List of Property objects.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.PropertyForbiddenException User has not enough rights to obtain one of requested properties.
		 * @throws ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException If one of requested properties was not found.
		 * @throws ITHit.WebDAV.Client.Exceptions.PropertyException Server returned unknown error for specific property.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		GetPropertyValues: function(aNames) {
			aNames = aNames || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.GetPropertyValues()');

			var oResult = ITHit.WebDAV.Client.Methods.Propfind.Go(
				oRequest,
				this.Href,
				ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
				aNames,
				ITHit.WebDAV.Client.Depth.Zero,
				this.Host
			);

			var oProperty = self.GetPropertyValuesFromMultiResponse(oResult.Response, this.Href);

			oRequest.MarkFinish();
			return oProperty;
		},

		/**
		 * Callback function to be called when item properties values loaded from server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~GetPropertyValuesAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 * @param {ITHit.WebDAV.Client.Property[]} oResult.Result List of Property objects.
		 */

		/**
		 * Retrieves values of specific properties.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyProperties.GetProperties.GetPropertyValues
		 * @param {ITHit.WebDAV.Client.PropertyName[]} aNames
		 * @param {ITHit.WebDAV.Client.HierarchyItem~GetPropertyValuesAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		GetPropertyValuesAsync: function(aNames, fCallback) {
			aNames = aNames || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.GetPropertyValuesAsync()');

			var that = this;
			ITHit.WebDAV.Client.Methods.Propfind.GoAsync(
				oRequest,
				this.Href,
				ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
				aNames,
				ITHit.WebDAV.Client.Depth.Zero,
				this.Host,
				function(oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						try {
							oAsyncResult.Result = self.GetPropertyValuesFromMultiResponse(oAsyncResult.Result.Response, that.Href);
						} catch(oError) {
							oAsyncResult.Error = oError;
							oAsyncResult.IsSuccess = false;
						}
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		/**
		 * Retrieves all custom properties exposed by the item.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @returns {ITHit.WebDAV.Client.Property[]} List of Property objects.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		GetAllProperties: function() {
			return this.GetPropertyValues(null);
		},

		/**
		 * Callback function to be called when all properties loaded from server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~GetAllPropertiesAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 * @param {ITHit.WebDAV.Client.Property[]} oResult.Result List of Property objects.
		 */

		/**
		 * Retrieves all custom properties exposed by the item.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyProperties.GetProperties.GetAllProperties
		 * @param {ITHit.WebDAV.Client.HierarchyItem~GetAllPropertiesAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		GetAllPropertiesAsync: function(fCallback) {
			return this.GetPropertyValuesAsync(null, fCallback);
		},

		/**
		 * Retrieves parent hierarchy item of this item.
		 * @private
		 * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. Default is empty array.
		 * @returns {ITHit.WebDAV.Client.Folder} Parent hierarchy item of this item. Null for root item.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		GetParent: function(aProperties) {
			aProperties = aProperties || [];

			var oRequest = this.Session.CreateRequest(this.__className + '.GetParent()');

			var sParentHref = ITHit.WebDAV.Client.HierarchyItem.GetFolderParentUri(ITHit.WebDAV.Client.Encoder.Decode(this.Href));
			if (sParentHref === null) {
				oRequest.MarkFinish();
				return null;
			}

			var oFolder = ITHit.WebDAV.Client.Folder.OpenItem(oRequest, sParentHref, aProperties);

			oRequest.MarkFinish();
			return oFolder;
		},

		/**
		 * Callback function to be called when parent folder loaded from server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~GetParentAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 * @param {ITHit.WebDAV.Client.Folder} oResult.Result Parent hierarchy item of this item. Null for root item.
		 */

		/**
		 * Retrieves parent hierarchy item of this item.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.GetParent.GetParent
		 * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. Default is empty array.
		 * @param {ITHit.WebDAV.Client.HierarchyItem~GetParentAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		GetParentAsync: function(aProperties, fCallback) {
			aProperties = aProperties || [];

			var oRequest = this.Session.CreateRequest(this.__className + '.GetParentAsync()');

			var sParentHref = ITHit.WebDAV.Client.HierarchyItem.GetFolderParentUri(ITHit.WebDAV.Client.Encoder.Decode(this.Href));
			if (sParentHref === null) {
				fCallback(new ITHit.WebDAV.Client.AsyncResult(null, true, null));
				return null;
			}

			ITHit.WebDAV.Client.Folder.OpenItemAsync(oRequest, sParentHref, aProperties, fCallback);

			return oRequest;
		},

		/**
		 * Retrieves media type independent links.
		 * @private
		 * @returns {ITHit.WebDAV.Client.Source[]|null} Media type independent links or null.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException If property is not supported.
		 * @throws ITHit.WebDAV.Client.Exceptions.PropertyException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		GetSource: function() {
			var oRequest = this.Session.CreateRequest(this.__className + '.GetSource()');

			var oResult = ITHit.WebDAV.Client.Methods.Propfind.Go(
				oRequest,
				this.Href,
				ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
				[
					ITHit.WebDAV.Client.DavConstants.Source
				],
				ITHit.WebDAV.Client.Depth.Zero,
				this.Host
			);

			var aSource = self.GetSourceFromMultiResponse(oResult.Response.Responses, this.Href);

			oRequest.MarkFinish();
			return aSource;
		},

		/**
		 * Callback function to be called when source loaded from server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~GetSourceAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 * @param {ITHit.WebDAV.Client.Source[]|null} oResult.Result Media type independent links or null.
		 */

		/**
		 * Retrieves media type independent links.
		 * @api
		 * @param {ITHit.WebDAV.Client.HierarchyItem~GetSourceAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		GetSourceAsync: function(fCallback) {
			var oRequest = this.Session.CreateRequest(this.__className + '.GetSourceAsync()');

			var that = this;
			ITHit.WebDAV.Client.Methods.Propfind.GoAsync(
				oRequest,
				this.Href,
				ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
				[
					ITHit.WebDAV.Client.DavConstants.Source
				],
				ITHit.WebDAV.Client.Depth.Zero,
				this.Host,
				function(oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						try {
							oAsyncResult.Result = self.GetSourceFromMultiResponse(oAsyncResult.Result.Response.Responses, that.Href);
						} catch(oError) {
							oAsyncResult.Error = oError;
							oAsyncResult.IsSuccess = false;
						}
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		/**
		 * Locks the item.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {string} sLockScope Scope of the lock.
		 * @param {boolean} bDeep Whether to lock entire subtree.
		 * @param {string} sOwner Owner of the lock.
		 * @param {number} iTimeout Timeout after which lock expires.
		 * @returns {ITHit.WebDAV.Client.LockInfo} Instance of LockInfo with information about created lock.
		 * @throws ITHit.WebDAV.Client.Exceptions.PreconditionFailedException The included lock token was not enforceable on this resource or the server could not satisfy the request in the lockinfo XML element.
		 * @throws ITHit.WebDAV.Client.Exceptions.LockedException The resource is locked. The method has been rejected.
		 * @throws ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException The item does not support locking.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException The item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		Lock: function(sLockScope, bDeep, sOwner, iTimeout) {
			var oRequest = this.Session.CreateRequest(this.__className + '.Lock()');

			var oResult = ITHit.WebDAV.Client.Methods.Lock.Go(
				oRequest,
				this.Href,
				iTimeout,
				sLockScope,
				this.Host,
				bDeep,
				sOwner
			);

			// Return response object.
			oRequest.MarkFinish();
			return oResult.LockInfo;
		},   	    

		/**
		 * Callback function to be called when item is locked on server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~LockAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 * @param {ITHit.WebDAV.Client.LockInfo} oResult.Result Instance of LockInfo with information about created lock.
		 */

		/**
		 * Locks the item. If the lock was successfully applied, the server will return a lock token. You will pass this
		 * lock token back to the server when updating and unlocking the item. The actual lock time applied by the server
		 * may be different from the one requested by the client.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.Locks.Lock.SetLock
		 * @param {string} sLockScope Scope of the lock. See LockScope Enumeration {@link ITHit.WebDAV.Client.LockScope}
		 * @param {boolean} bDeep Whether to lock entire subtree.
		 * @param {string} sOwner Owner of the lock.
		 * @param {number} iTimeout Timeout after which lock expires. Pass -1 to request an infinite timeout.
		 * @param {ITHit.WebDAV.Client.HierarchyItem~LockAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		LockAsync: function(sLockScope, bDeep, sOwner, iTimeout, fCallback) {
			var oRequest = this.Session.CreateRequest(this.__className + '.LockAsync()');

			ITHit.WebDAV.Client.Methods.Lock.GoAsync(
				oRequest,
				this.Href,
				iTimeout,
				sLockScope,
				this.Host,
				bDeep,
				sOwner,
				function (oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						oAsyncResult.Result = oAsyncResult.Result.LockInfo;
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		/**
		 * Moves this item to another location.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {ITHit.WebDAV.Client.Folder} oDestinationFolder Folder to move to.
		 * @param {string} sDestinationName Name to assign to moved item.
		 * @param {boolean} bOverwrite Whether existing destination item shall be overwritten.
		 * @param {(string|ITHit.WebDAV.Client.LockUriTokenPair[])} [oLockTokens] Lock tokens for item to be moved, for destination folder or file to be overwritten that are locked.
		 * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException The source and destination URIs are the same.
		 * @throws ITHit.WebDAV.Client.Exceptions.ConflictException A resource cannot be created at the destination until one or more intermediate collections have been created.
		 * @throws ITHit.WebDAV.Client.Exceptions.PreconditionFailedException The destination resource exists and overwrite was false.
		 * @throws ITHit.WebDAV.Client.Exceptions.LockedException The destination folder or items to be overwritten were locked or source items were locked.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error for specific resource.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		MoveTo: function(oDestinationFolder, sDestinationName, bOverwrite, oLockTokens) {
			bOverwrite  = bOverwrite || false;
			oLockTokens = oLockTokens || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.MoveTo()');

			// Check destination type.
			if (!(oDestinationFolder instanceof ITHit.WebDAV.Client.Folder)) {
				oRequest.MarkFinish();
				throw new ITHit.Exception(ITHit.Phrases.Exceptions.FolderWasExpectedAsDestinationForMoving);
			}

			// Move item.
			var oResult = ITHit.WebDAV.Client.Methods.CopyMove.Go(
				oRequest,
				ITHit.WebDAV.Client.Methods.CopyMove.Mode.Move,
				this.Href,
				ITHit.WebDAV.Client.HierarchyItem.AppendToUri(oDestinationFolder.Href, sDestinationName),
				this.ResourceType,
				true,
				bOverwrite,
				oLockTokens,
				this.Host
			);

			var oError = this._GetErrorFromMoveResponse(oResult.Response);
			if (oError !== null) {
				oRequest.MarkFinish();
				throw oError;
			}

			oRequest.MarkFinish();
		},

		/**
		 * Callback function to be called when item is moved on server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~MoveToAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Moves this item to another location.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.CopyMove.Move
		 * @param {ITHit.WebDAV.Client.Folder} oDestinationFolder Folder to move to.
		 * @param {string} sDestinationName Name to assign to moved item.
		 * @param {boolean} bOverwrite Whether existing destination item shall be overwritten.
		 * @param {(string|ITHit.WebDAV.Client.LockUriTokenPair[])} oLockTokens Lock tokens for item to be moved, for destination folder or file to be overwritten that are locked.
		 * @param {ITHit.WebDAV.Client.HierarchyItem~MoveToAsyncCallback} fCallback Function to call when operation is completed.
		 * @return {ITHit.WebDAV.Client.Request} Request object.
		 */
		MoveToAsync: function(oDestinationFolder, sDestinationName, bOverwrite, oLockTokens, fCallback) {
			bOverwrite  = bOverwrite || false;
			oLockTokens = oLockTokens || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.MoveToAsync()');

			// Check destination type.
			if (!(oDestinationFolder instanceof ITHit.WebDAV.Client.Folder)) {
				oRequest.MarkFinish();
				throw new ITHit.Exception(ITHit.Phrases.Exceptions.FolderWasExpectedAsDestinationForMoving);
			}

			var that = this;
			ITHit.WebDAV.Client.Methods.CopyMove.GoAsync(
				oRequest,
				ITHit.WebDAV.Client.Methods.CopyMove.Mode.Move,
				this.Href,
				ITHit.WebDAV.Client.HierarchyItem.AppendToUri(oDestinationFolder.Href, sDestinationName),
				this.ResourceType,
				true,
				bOverwrite,
				oLockTokens,
				this.Host,
				function(oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						oAsyncResult.Error = that._GetErrorFromMoveResponse(oAsyncResult.Result.Response);
						if (oAsyncResult.Error !== null) {
							oAsyncResult.IsSuccess = false;
							oAsyncResult.Result = null;
						}
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		/**
		 * Prolongs the lock.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {string} sLockToken Identifies lock to be prolonged.
		 * @param {number} iTimeout New timeout to set.
		 * @returns {ITHit.WebDAV.Client.LockInfo} Instance of LockInfo with information about refreshed lock.
		 * @throws ITHit.WebDAV.Client.Exceptions.PreconditionFailedException The included lock token was not enforceable on this resource or the server could not satisfy the request in the lockinfo XML element.
		 * @throws ITHit.WebDAV.Client.Exceptions.LockedException The resource is locked, so the method has been rejected.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		RefreshLock: function(sLockToken, iTimeout) {

			var oRequest = this.Session.CreateRequest(this.__className + '.RefreshLock()');

			var oResult = ITHit.WebDAV.Client.Methods.LockRefresh.Go(
				oRequest,
				this.Href,
				iTimeout,
				sLockToken,
				this.Host
			);

			// Return lock info object.
			oRequest.MarkFinish();
			return oResult.LockInfo;
		},

		/**
		 * Callback function to be called when item lock is refreshed on server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~RefreshLockAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 * @param {ITHit.WebDAV.Client.LockInfo} oResult.Result Instance of LockInfo with information about refreshed lock.
		 */

		/**
		 * Prolongs the lock.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.Locks.RefreshLock.RefreshLock
		 * @param {string} sLockToken Identifies lock to be prolonged.
		 * @param {number} iTimeout New timeout to set.
		 * @param {ITHit.WebDAV.Client.HierarchyItem~RefreshLockAsyncCallback} fCallback Function to call when operation is completed.
		 * @return {ITHit.WebDAV.Client.Request} Request object.
		 */
		RefreshLockAsync: function(sLockToken, iTimeout, fCallback) {

			var oRequest = this.Session.CreateRequest(this.__className + '.RefreshLockAsync()');

			ITHit.WebDAV.Client.Methods.LockRefresh.GoAsync(
				oRequest,
				this.Href,
				iTimeout,
				sLockToken,
				this.Host,
				function (oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						oAsyncResult.Result = oAsyncResult.Result.LockInfo;
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		/**
		 * Gets features supported by this item, such as WebDAV class support.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @returns {ITHit.WebDAV.Client.OptionsInfo} OptionsInfo object containing information about features supported by server.
		 */
		SupportedFeatures: function() {

			var oRequest = this.Session.CreateRequest(this.__className + '.SupportedFeatures()');
			var oOptions = ITHit.WebDAV.Client.Methods.Options.Go(oRequest, this.Href, this.Host).ItemOptions;

			oRequest.MarkFinish();
			return oOptions;
		},

		/**
		 * Gets features supported by this item, such as WebDAV class support.
		 * @private
		 * @deprecated Use GetSupportedFeaturesAsync method
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.SupportedFeatures.SupportedFeatures
		 * @param {ITHit.WebDAV.Client.HierarchyItem~GetSupportedFeaturesAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		SupportedFeaturesAsync: function (fCallback) {
			return this.GetSupportedFeaturesAsync(fCallback);
		},

		/**
		 * Callback function to be called when options info loaded from server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~GetSupportedFeaturesAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 * @param {ITHit.WebDAV.Client.OptionsInfo} oResult.Result OptionsInfo object containing information about features supported by server.
		 */

		/**
		 * Gets features supported by this item, such as WebDAV class support.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.SupportedFeatures.SupportedFeatures
		 * @param {ITHit.WebDAV.Client.HierarchyItem~GetSupportedFeaturesAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		GetSupportedFeaturesAsync: function (fCallback) {

			var oRequest = this.Session.CreateRequest(this.__className + '.GetSupportedFeaturesAsync()');

			ITHit.WebDAV.Client.Methods.Options.GoAsync(oRequest, this.Href, this.Host, function(oAsyncResult) {
				if (oAsyncResult.IsSuccess) {
					oAsyncResult.Result = oAsyncResult.Result.ItemOptions;
				}

				oRequest.MarkFinish();
				fCallback(oAsyncResult);
			});

			return oRequest;
		},

		/**
		 * Removes the lock.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {string} [sLockToken] Identifies lock to be prolonged.
		 * @throws ITHit.WebDAV.Client.Exceptions.PreconditionFailedException The item is not locked.
		 * @throws ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException The item does not support locking.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException The item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		Unlock: function(sLockToken) {

			var oRequest = this.Session.CreateRequest(this.__className + '.Unlock()');

			// Unlock item.
			var oResult = ITHit.WebDAV.Client.Methods.Unlock.Go(
				oRequest,
				this.Href,
				sLockToken,
				this.Host
			);

			var oError = this._GetErrorFromUnlockResponse(oResult.Response);
			if (oError) {
				oRequest.MarkFinish();
				throw oError;
			}

			oRequest.MarkFinish();
		},

		/**
		 * Callback function to be called when item unlocked on server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~UnlockAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Removes the lock.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.Locks.Lock.SetUnLock
		 * @param {string} sLockToken Identifies lock to be prolonged.
		 * @param {ITHit.WebDAV.Client.HierarchyItem~UnlockAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		UnlockAsync: function(sLockToken, fCallback) {

			var oRequest = this.Session.CreateRequest(this.__className + '.UnlockAsync()');

			var that = this;
			ITHit.WebDAV.Client.Methods.Unlock.GoAsync(
				oRequest,
				this.Href,
				sLockToken,
				this.Host,
				function (oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						oAsyncResult.Error = that._GetErrorFromUnlockResponse(oAsyncResult.Result.Response);
						if (oAsyncResult.Error !== null) {
							oAsyncResult.IsSuccess = false;
							oAsyncResult.Result = null;
						}
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},	    

		/**
		 * Updates values of properties exposed by this item.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {ITHit.WebDAV.Client.Property[]} oPropertiesToAddOrUpdate Properties to be updated.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} oPropertiesToDelete Names of properties to be removed from this item.
		 * @param {string} [sLockToken] Lock token.
		 * @throws ITHit.WebDAV.Client.Exceptions.LockedException The item is locked and no or invalid lock token was provided.
		 * @throws ITHit.WebDAV.Client.Exceptions.PropertyForbiddenException Cannot alter one of the properties.
		 * @throws ITHit.WebDAV.Client.Exceptions.PropertyConflictException The client has provided a value whose semantics are not appropriate for the property. This includes trying to set read-only properties.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.PropertyException Server returned unknown error for specific property.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		UpdateProperties: function(oPropertiesToAddOrUpdate, oPropertiesToDelete, sLockToken) {
			sLockToken = sLockToken || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.UpdateProperties()');

			// Properties
			var aPropsToAddOrUpdate = this._GetPropertiesForUpdate(oPropertiesToAddOrUpdate);
			var aPropsToDelete      = this._GetPropertiesForDelete(oPropertiesToDelete);

			// Check whether there is something to change.
			if (aPropsToAddOrUpdate.length + aPropsToDelete.length === 0) {
				ITHit.Logger.WriteMessage(ITHit.Phrases.Exceptions.NoPropertiesToManipulateWith);
				oRequest.MarkFinish();
				return;
			}

			var oResult = ITHit.WebDAV.Client.Methods.Proppatch.Go(
				oRequest,
				this.Href,
				aPropsToAddOrUpdate,
				aPropsToDelete,
				sLockToken,
				this.Host
			);

			var oError = this._GetErrorFromUpdatePropertiesResponse(oResult.Response);
			if (oError) {
				oRequest.MarkFinish();
				throw oError;
			}

			oRequest.MarkFinish();
		},

		/**
		 * Callback function to be called when item properties is updated on server.
		 * @callback ITHit.WebDAV.Client.HierarchyItem~UpdatePropertiesAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Updates values of properties exposed by this item.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyProperties.UpdateProperties.Update
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyProperties.UpdateProperties.Delete
		 * @param {ITHit.WebDAV.Client.Property[]} oPropertiesToAddOrUpdate Properties to be updated.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} oPropertiesToDelete Names of properties to be removed from this item.
		 * @param {string} [sLockToken] Lock token.
		 * @param {ITHit.WebDAV.Client.HierarchyItem~UpdatePropertiesAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.WebDavRequest|null} WebDAV request
		 */
		UpdatePropertiesAsync: function(oPropertiesToAddOrUpdate, oPropertiesToDelete, sLockToken, fCallback) {
			sLockToken = sLockToken || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.UpdatePropertiesAsync()');

			// Properties
			var aPropsToAddOrUpdate = this._GetPropertiesForUpdate(oPropertiesToAddOrUpdate);
			var aPropsToDelete      = this._GetPropertiesForDelete(oPropertiesToDelete);

			// Check whether there is something to change.
			if (aPropsToAddOrUpdate.length + aPropsToDelete.length === 0) {
				oRequest.MarkFinish();
				fCallback(new ITHit.WebDAV.Client.AsyncResult(true, true, null));
				return null;
			}

			var that = this;
			ITHit.WebDAV.Client.Methods.Proppatch.GoAsync(
				oRequest,
				this.Href,
				aPropsToAddOrUpdate,
				aPropsToDelete,
				sLockToken,
				this.Host,
				function(oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						oAsyncResult.Error = that._GetErrorFromUpdatePropertiesResponse(oAsyncResult.Result.Response);
						if (oAsyncResult.Error !== null) {
							oAsyncResult.IsSuccess = false;
							oAsyncResult.Result = null;
						}
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		_GetPropertiesForUpdate: function(oPropertiesToAddOrUpdate) {
			// Define variables for properties.
			var aPropsToAddOrUpdate = [];

			// Add or update properties.
			if (oPropertiesToAddOrUpdate) {
				for (var i = 0; i < oPropertiesToAddOrUpdate.length; i++) {
					if ( (oPropertiesToAddOrUpdate[i] instanceof ITHit.WebDAV.Client.Property) && oPropertiesToAddOrUpdate[i]) {
						if (oPropertiesToAddOrUpdate[i].Name.NamespaceUri != ITHit.WebDAV.Client.DavConstants.NamespaceUri) {
							aPropsToAddOrUpdate.push(oPropertiesToAddOrUpdate[i]);
						} else  {
							throw new ITHit.WebDAV.Client.Exceptions.PropertyException(ITHit.Phrases.Exceptions.AddOrUpdatePropertyDavProhibition.Paste(oPropertiesToAddOrUpdate[i]), this.Href, oPropertiesToAddOrUpdate[i]);
						}
					} else {
						throw new ITHit.WebDAV.Client.Exceptions.PropertyException(ITHit.Phrases.Exceptions.PropertyUpdateTypeException);
					}
				}
			}

			return aPropsToAddOrUpdate;
		},

		_GetPropertiesForDelete: function(oPropertiesToDelete) {
			// Define variables for properties.
			var aPropsToDelete      = [];

			// Delete properties.
			if (oPropertiesToDelete) {
				for (var i = 0; i < oPropertiesToDelete.length; i++) {
					if ( (oPropertiesToDelete[i] instanceof ITHit.WebDAV.Client.PropertyName) && oPropertiesToDelete[i]) {
						if (oPropertiesToDelete[i].NamespaceUri != ITHit.WebDAV.Client.DavConstants.NamespaceUri) {
							aPropsToDelete.push(oPropertiesToDelete[i]);
						} else {
							throw new ITHit.WebDAV.Client.Exceptions.PropertyException(ITHit.Phrases.Exceptions.DeletePropertyDavProhibition.Paste(oPropertiesToDelete[i]), this.Href, oPropertiesToDelete[i]);
						}
					} else {
						throw new ITHit.WebDAV.Client.Exceptions.PropertyException(ITHit.Phrases.Exceptions.PropertyDeleteTypeException);
					}
				}
			}

			return aPropsToDelete;
		},

		_GetErrorFromDeleteResponse: function(oResponse) {
			// Whether response is instance of MultiResponse class.
			if (oResponse instanceof ITHit.WebDAV.Client.Methods.MultiResponse) {
				return new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(
					ITHit.Phrases.FailedToDelete,
					this.Href,
					new ITHit.WebDAV.Client.Exceptions.Info.Multistatus(oResponse),
					ITHit.WebDAV.Client.HttpStatus.MultiStatus,
					null
				);
			}

			// Whether response is instance of SingleResponse class.
			if (oResponse instanceof ITHit.WebDAV.Client.Methods.SingleResponse && !oResponse.Status.IsSuccess()) {
				var sMessage = ITHit.Phrases.DeleteFailedWithStatus.Paste(oResponse.Status.Code, oResponse.Status.Description);
				return new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(sMessage, this.Href, null, oResponse.Status, null);
			}

			return null;
		},

		_GetErrorFromCopyResponse: function(oResponse) {
			if (oResponse instanceof ITHit.WebDAV.Client.Methods.MultiResponse) {
				for (var i = 0, l = oResponse.Responses.length; i < l; i++) {
					if (oResponse.Responses[i].Status.IsCopyMoveOk()) {
						continue;
					}

					return new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(
						ITHit.Phrases.FailedToCopy,
						this.Href,
						new ITHit.WebDAV.Client.Exceptions.Info.Multistatus(oResponse),
						ITHit.WebDAV.Client.HttpStatus.MultiStatus,
						null
					);
				}
			}

			if (oResponse instanceof ITHit.WebDAV.Client.Methods.SingleResponse && !oResponse.Status.IsCopyMoveOk()) {
				return new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(
					ITHit.Phrases.FailedToCopyWithStatus.Paste(oResponse.Status.Code, oResponse.Status.Description),
					this.Href,
					null,
					oResponse.Status,
					null
				);
			}

			return null;
		},

		_GetErrorFromMoveResponse: function(oResponse) {
			if (oResponse instanceof ITHit.WebDAV.Client.Methods.MultiResponse) {
				for (var i = 0, l = oResponse.Responses.length; i < l; i++) {
					if (oResponse.Responses[i].Status.IsCopyMoveOk()) {
						continue;
					}

					return new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(
						ITHit.Phrases.FailedToMove,
						this.Href,
						new ITHit.WebDAV.Client.Exceptions.Info.Multistatus(oResponse),
						ITHit.WebDAV.Client.HttpStatus.MultiStatus,
						null
					);
				}
			}

			if (oResponse instanceof ITHit.WebDAV.Client.Methods.SingleResponse && !oResponse.Status.IsCopyMoveOk()) {
				return new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(
					ITHit.Phrases.MoveFailedWithStatus.Paste(oResponse.Status.Code, oResponse.Status.Description),
					this.Href,
					null,
					oResponse.Status,
					null
				);
			}

			return null;
		},

		_GetErrorFromUnlockResponse: function(oResponse) {

			// Check status.
			if (!oResponse.Status.IsUnlockOk()) {
				return new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(
					ITHit.Phrases.UnlockFailedWithStatus.Paste(oResponse.Status.Code, oResponse.Status.Description),
					this.Href,
					null,
					oResponse.Status,
					null
				);
			}

			return null;
		},

		_GetErrorFromUpdatePropertiesResponse: function(oResponse) {
			var oMultistatus = new ITHit.WebDAV.Client.Exceptions.Info.PropertyMultistatus(oResponse);

			for (var i = 0; i < oMultistatus.Responses.length; i++) {
				var oPropResp = oMultistatus.Responses[i];
				if (oPropResp.Status.IsSuccess()) {
					continue;
				}

				return new ITHit.WebDAV.Client.Exceptions.PropertyException(
					ITHit.Phrases.FailedToUpdateProp,
					this.Href,
					oPropResp.PropertyName,
					oMultistatus,
					ITHit.WebDAV.Client.HttpStatus.MultiStatus,
					null
				);
			}

			return null;
		}

	});

})();

/**
 * @class ITHit.WebDAV.Client.Methods.Put
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Put', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Put.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Put */{

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param sContentType
		 * @param sContent
		 * @param sLockToken
		 * @param sHost
		 * @returns {*}
		 */
		Go: function (oRequest, sHref, sContentType, sContent, sLockToken, sHost) {
			return this._super.apply(this, arguments);
		},

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param sContentType
		 * @param sContent
		 * @param sLockToken
		 * @param sHost
		 * @param fCallback
		 * @returns {*}
		 */
		GoAsync: function (oRequest, sHref, sContentType, sContent, sLockToken, sHost, fCallback) {
			return this._super.apply(this, arguments);
		},

		_CreateRequest: function (oRequest, sHref, sContentType, sContent, sLockToken, sHost) {

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref, sLockToken);

			// Set method.
			oWebDavRequest.Method('PUT');

			// Add headers.
			if (sContentType) {
				// MSXML does not allow empty Content-Type header. Tested with MSXML 3.0 SP5
				oWebDavRequest.Headers.Add('Content-Type', sContentType);
			}

			// Assign content body.
			oWebDavRequest.Body(sContent);

			// Return request.
			return oWebDavRequest;
		}

	}
});


/**
 * @class ITHit.WebDAV.Client.Methods.Get
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Get', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Get.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Get */{

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param iBytesFrom
		 * @param iBytesTo
		 * @param sHost
		 * @returns {*}
		 */
		Go: function (oRequest, sHref, iBytesFrom, iBytesTo, sHost) {
			return this._super.apply(this, arguments);
		},

		/**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param iBytesFrom
		 * @param iBytesTo
		 * @param sHost
		 * @returns {*}
		 * @constructor
		 */
		GoAsync: function (oRequest, sHref, iBytesFrom, iBytesTo, sHost) {
			return this._super.apply(this, arguments);
		},

		_CreateRequest: function (oRequest, sHref, iBytesFrom, iBytesTo, sHost) {

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref);

			// Set method.
			oWebDavRequest.Method('GET');

			// Add headers.
			oWebDavRequest.Headers.Add('Translate', 'f');

			// Check whether byte-range is specified.
			if (iBytesFrom !== null) {

				var sByteRange = iBytesFrom;

				if (iBytesFrom >= 0) {
					if (iBytesTo !== null) {
						sByteRange += '-' + parseInt(iBytesTo);
					} else {
						sByteRange += '-';
					}
				} else {
					sByteRange = String(sByteRange);
				}

				// Set byte-range header.
				oWebDavRequest.Headers.Add('Range', 'bytes=' + sByteRange);
			}

			// Return request.
			return oWebDavRequest;
		}

	},

	GetContent: function () {
		return this.Response._Response.BodyText;
	}
});

;
(function() {

/**
 * The class represents set of extensions to be edited with Microsoft Office.
 * @api
 * @class ITHit.WebDAV.Client.MsOfficeEditExtensions
 * @examplecode ITHit.WebDAV.Client.Tests.DocManager.MsOfficeEditExtensions.EditRtfDocumentWithWord
 */
var self = ITHit.DefineClass('ITHit.WebDAV.Client.MsOfficeEditExtensions', null, /** @lends ITHit.WebDAV.Client.MsOfficeEditExtensions.prototype */{
	__static: /** @lends ITHit.WebDAV.Client.MsOfficeEditExtensions */{
		/**
		 * get schema by file extension
		 * @return sSchema {string | null}
		 * @param sExt {string}
		 */
		GetSchema: function(sExt) {
			var sResult = null;
			var oSchemas = {
				'Access': 'ms-access',
				'Infopath': 'ms-infopath',
				'Project': 'ms-project',
				'Publisher': 'ms-publisher',
				'Visio': 'ms-visio',
				'Word': 'ms-word',
				'Powerpoint': 'ms-powerpoint',
				'Excel': 'ms-excel'
			};
			var aSchemas = Object.keys(oSchemas);
			sExt = sExt.toLowerCase();
			for (var i = 0, l = aSchemas.length; i < l; i++) {
				var sSchema = aSchemas[i];
				var aExtensions = self[sSchema];
				for (var j = 0, m = aExtensions.length; j < m; j++) {
					if (aExtensions[j] === sExt) {
						sResult = oSchemas[sSchema];
						break;
					}
				}
				if (sResult !== null) {
					break;
				}
			}
			return sResult;
		},

		/**
		 * Array of file extensions which are opened with Microsoft Access.
		 * @api
		 * @type {array}
		 */
		Access: [
			"accdb",
			"mdb"
		],

		/**
		 * Array of file extensions which are opened with Microsoft Infopath.
		 * @api
		 * @type {array}
		 */
		Infopath: [
			"xsn",
			"xsf"
		],

		/**
		 * Array of file extensions which are opened with Microsoft Excel.
		 * @api
		 * @type {array}
		 */
		Excel: [
			"xltx",
			"xltm",
			"xlt",
			"xlsx",
			"xlsm",
			"xlsb",
			"xls",
			"xll",
			"xlam",
			"xla",
			"ods"
		],

		/**
		 * Array of file extensions which are opened with Microsoft Powerpoint.
		 * @api
		 * @type {array}
		 */
		Powerpoint: [
			"pptx",
			"pptm",
			"ppt",
			"ppsx",
			"ppsm",
			"pps",
			"ppam",
			"ppa",
			"potx",
			"potm",
			"pot",
			"odp"
		],

		/**
		 * Array of file extensions which are opened with Microsoft Project.
		 * @api
		 * @type {array}
		 */
		Project: [
			"mpp",
			"mpt"
		],

		/**
		 * Array of file extensions which are opened with Microsoft Publisher.
		 * @api
		 * @type {array}
		 */
		Publisher: [
			"pub"
		],

		/**
		 * Array of file extensions which are opened with Microsoft Visio.
		 * @api
		 * @type {array}
		 */
		Visio: [
			"vstx",
			"vstm",
			"vst",
			"vssx",
			"vssm",
			"vss",
			"vsl",
			"vsdx",
			"vsdm",
			"vsd",
			"vdw"
		],

		/**
		 * Array of file extensions which are opened with Microsoft Word.
		 * @api
		 * @type {array}
		 */
		Word: [
			"docx",
			"doc",
			"docm",
			"dot",
			"dotm",
			"dotx",
			"odt"
		]
	}
});

})();

/**
 * Base exception for all exceptions thrown by browser extension integration.
 * Initializes a new instance of the IntegrationException class with a specified error message.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.IntegrationException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.IntegrationException', ITHit.WebDAV.Client.Exceptions.WebDavException,
    /** @lends ITHit.WebDAV.Client.Exceptions.IntegrationException.prototype */{

        /**
         * Exception name
         * @type {string}
         */
        Name: 'IntegrationException',

        /**
         * @param {string} sMessage The error message string.
         * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
         */
        constructor: function (sMessage, oInnerException) {
            this._super(sMessage, oInnerException);
        }

    });
;
(function () {

	/**
	 * This class provides methods for working with browser extensions. This include checking protocol version and
	 * supported [Office URI Schemes]{@link https://msdn.microsoft.com/en-us/library/office/dn906146.aspx}.
	 * @package
	 * @class ITHit.WebDAV.Client.BrowserExtension
	 */
	var self = ITHit.DefineClass('ITHit.WebDAV.Client.BrowserExtension', null, {
		__static: /** @lends ITHit.WebDAV.Client.BrowserExtension */{

			/**
			 * Name of protocol. Used as identifier for interact with browser extension.
			 * @private
			 * @readonly
			 * @type {string}
			 */
			_ProtocolName: ITHit.WebDAV.Client.DavConstants.ProtocolName,

			/**
			 * Time to wait while extension fill data.
			 * @private
			 * @type {int}
			 */
			_Timeout: 100,


			/**
			 * Callback function to be called when  protocol version retrieved.
			 * @callback ITHit.WebDAV.Client.BrowserExtension~GetDavProtocolAppVersionAsyncCallback
			 * @param {ITHit.WebDAV.Client.AsyncResult} oAsyncResult Result object
			 * @param {string} oAsyncResult.Result Protocol version.
			 */


			/**
			 * This function get protocol version asynchronously
			 * If browser extension does not fill data in <code>'_Timeout'</code> time, or error occurred <<code>'successCallback'</code> called with null.
			 * @api
			 * @param {ITHit.WebDAV.Client.BrowserExtension~GetDavProtocolAppVersionAsync} fCallback Function to call when operation is completed.
			 */
			GetDavProtocolAppVersionAsync: function (fCallback) {
				self._GetExtensionPropertyAsync("version", fCallback);
			},


			/**
			 * Callback function to be called when  protocol support checked.
			 * @api
			 * @callback ITHit.WebDAV.Client.BrowserExtension~IsProtocolAvailableAsyncCallback
			 * @param {ITHit.WebDAV.Client.AsyncResult} oAsyncResult Result object
			 * @param {boolean} oAsyncResult.Result Is protocol supported.
			 */

			/**
			 * This function check if Office URI Scheme installed for file extension.
			 * If browser extension does not fill data in <code>'_Timeout'</code>, or error occurred <code>'successCallback'</code> called with false.
			 * @api
			 * @param {string} [sExt] File extension.
			 * @param {ITHit.WebDAV.Client.BrowserExtension~IsProtocolAvailableAsync} fCallback Function to call when operation is completed.
			 */
			IsProtocolAvailableAsync: function (sExt, fCallback) {
				self._GetExtensionPropertyAsync("",
					function (oAsyncResult) {
						if (!oAsyncResult.IsSuccess) {
							fCallback(oAsyncResult);
							return;
						}

						var aSchemas = oAsyncResult.Result.split(",");
						var sSchema = ITHit.WebDAV.Client.MsOfficeEditExtensions.GetSchema(sExt);
						oAsyncResult.Result = ITHit.Utils.Contains(aSchemas, sSchema);
						fCallback(oAsyncResult);
					});
			},

			/**
             * This function check if extension installed.
             * @return {boolean}
             */
			IsExtensionInstalled: function () {
				return self.IsExtensionInstalled(true);
			},
			
			/**
             * This function check if extension installed.
			 * @param isMajorVersionCheck If we didn't find protocol name in data tag, then check major version for protocol name
             * @return {boolean}
             */
			IsExtensionInstalled: function (isMajorVersionCheck) {
				if(isMajorVersionCheck == null)
					isMajorVersionCheck = true;
				if (self._IsFailed())
					  return false;
                var sRegExpString = '^data-' + this._ProtocolName + '-.*';
                var oRegExp = new RegExp(sRegExpString);
                var oAttributes = document.documentElement.attributes;
                var bResult = false;
                for(var i = 0; i < oAttributes.length; i++)
				{
					if(oRegExp.test(oAttributes[i].name)) {
						bResult = true;
						break;
                    }
				}
				// If we didn't find protocol name in data tag, then check major version
                // This section added to let not Browsers extensions with no native host support (not Chrome) be able to work with earlier dav protocols. 
                // For ex.extension compiled for dav8, but website works with dav7.
				if(!bResult && isMajorVersionCheck){
					var ajaxlibVersion = ITHit.WebDAV.Client.WebDavSession.Version;
					sRegExpString = '^data-dav(.*)-version';
					oRegExp = new RegExp(sRegExpString);
					for(var i = 0; i < oAttributes.length; i++){
                        if (oRegExp.test(oAttributes[i].name)) {
                            var installedVersion = oAttributes[i].value;
                            if (installedVersion.split('.')[0] == ajaxlibVersion.split('.')[0]) {
								bResult = true;
								break;
							}
						}
					}
				}

                return bResult;
            },

			/**
			 * This function used to get the biggest protocol name from attributes 'data-dav(protocol_version)-version' filled by extension. 
			 * @private
			 */
            _GetInstalledExtensionBiggestProtocolName: function () {
                var protocolVersion = 0;
                var ajaxlibVersion = ITHit.WebDAV.Client.WebDavSession.Version;
                var oAttributes = document.documentElement.attributes;
                var sRegExpString = '^data-dav(.*)-version';
                var oRegExp = new RegExp(sRegExpString);
                for (var i = 0; i < oAttributes.length; i++) {
                    if (oRegExp.test(oAttributes[i].name)) {
                        var match = oRegExp.exec(oAttributes[i].name);
                        var extProtocol = parseInt(match[1]);
                        var installedVersion = oAttributes[i].value;
                        if (installedVersion.split('.')[0] == ajaxlibVersion.split('.')[0] &&
                            extProtocol > protocolVersion)
                            protocolVersion = extProtocol;
                    }
                }
                return 'dav'+protocolVersion;
            },
			
			/**
			 * This function used to get data from attribute  filled by extension.
			 * If extension does not fill data in <code>'_Timeout'</code> time, or error occurred <code>'successCallback'</code> called with null.
			 * @private
			 * @param {string} [sName] Attribute postfix.
			 * @param {function} [successCallback] Function to call if attribute can be read. Result is send as argument.
			 */
			_GetExtensionPropertyAsync: function (sName, fCallback) {
				var protocolName = self._GetInstalledExtensionBiggestProtocolName();
				
				var sAttributePrefix = "data-" + protocolName; //self._ProtocolName;
				var sAttributeName = sName.length > 0
					? sAttributePrefix + "-" + sName
					: sAttributePrefix;

				if (self._IsFailed()) {
					var oResult = new ITHit.WebDAV.Client.AsyncResult(null, false, self._GetException());
					fCallback(oResult);
				} else if (self._IsPending()) {
					setTimeout(function () {
						if (self._IsPending()) {
							var oResult = new ITHit.WebDAV.Client.AsyncResult(null, false, self._GetTimeoutException());
							fCallback(oResult);
							return;
						}

						if (self._IsFailed()) {
							var oResult = new ITHit.WebDAV.Client.AsyncResult(null, false, self._GetException());
							fCallback(oResult);
							return;
						}

						var oResult = new ITHit.WebDAV.Client.AsyncResult(document.documentElement.getAttribute(sAttributeName), true, null);
						fCallback(oResult);
					}, self.TimeOut);
				} else {
					var oResult = new ITHit.WebDAV.Client.AsyncResult(document.documentElement.getAttribute(sAttributeName), true, null);
					fCallback(oResult);
				}
			},

			/**
			 * This function used to check if extension is pending data.
			 * @private
			 * @returns {Boolean}
			 */
			_IsPending: function () {
				var sPendingAttributeName = "data-" + self._ProtocolName + "-pending";
				var isPending = document.documentElement.hasAttribute(sPendingAttributeName);
				return isPending;
			},

			/**
			 * This function used to check if extension is failed.
			 * @private
			 * @returns {Boolean}
			 */
			_IsFailed: function () {
				var sErrorAttributeName = "data-" + self._ProtocolName + "-error";
				var isFailed = document.documentElement.hasAttribute(sErrorAttributeName);
				return isFailed;
			},

			_GetTimeoutException: function () {
				var exception =  new ITHit.WebDAV.Client.Exceptions.IntegrationException(ITHit.Phrases.Exceptions.IntegrationTimeoutException.Paste(self._Timeout));
				return exception;
			},

			_GetException: function () {
				var errorAttributeName = "data-" + self._ProtocolName + "-error";
				var exception = new ITHit.WebDAV.Client.Exceptions.IntegrationException(document.documentElement.getAttribute(errorAttributeName));
				return exception;
			}
		}
	});
})();

/**
 * @private
 * @class ITHit.WebDAV.Client.Methods.GRemovePreview
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.GRemovePreview', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.GRemovePreview.prototype */{

    __static: /** @lends ITHit.WebDAV.Client.Methods.GRemovePreview */{

        /**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param sLockToken
		 * @returns {ITHit.WebDAV.Client.Methods.GRemovePreview}
		 */
        Go: function (oRequest, sHref) {
            return this._super.apply(this, arguments);
        },

        /**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param sLockToken
		 * @param fCallback
		 * @returns {*}
		 */
        GoAsync: function (oRequest, sHref, fCallback) {       
            return this._super.apply(this, arguments);
        },

        _ProcessResponse: function (oResponse, sHref) {
            // Get appropriate response object.
            var oResp = new ITHit.WebDAV.Client.Methods.SingleResponse(oResponse);

            return this._super(oResp);
        },

        _CreateRequest: function (oRequest, sHref) {  
            // Create request.
            var oWebRequest = oRequest.CreateWebDavRequest(null, sHref);
            oWebRequest.Method('GREMOVEPREVIEW');

            return oWebRequest;
        }

    }
});


/**
 * @private
 * @class ITHit.WebDAV.Client.Methods.GPreview
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.GPreview', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.GPreview.prototype */{

    __static: /** @lends ITHit.WebDAV.Client.Methods.GPreview */{

        /**
		 *
		 * @param oRequest
		 * @param sHref
		 * @returns {ITHit.WebDAV.Client.Methods.GPreview}
		 */
        Go: function (oRequest, sHref) {
            return this._super.apply(this, arguments);
        },

        /**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param fCallback
		 * @returns {*}
		 */
        GoAsync: function (oRequest, sHref, fCallback) {
            return this._super.apply(this, arguments);
        },

        _CreateRequest: function (oRequest, sHref) {
            // Create request.
            var oWebRequest = oRequest.CreateWebDavRequest(null, sHref);
            oWebRequest.Method('GPREVIEW');

            return oWebRequest;
        },
    },

    /**
    * @type string
    */
    GFileID: null,

    _Init: function () {         
        // Get response data as string.
        var oXmlDoc = this.Response.GetResponseStream();

        // Create namespace resolver.
        var oResolver = new ITHit.XPath.resolver();
        oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);
        oResolver.add('ithit', "https://www.ithit.com/gpreviewschema/");
       
        // Select property element.
        var oProp = new ITHit.WebDAV.Client.Property(ITHit.XPath.selectSingleNode('/d:prop', oXmlDoc, oResolver));

        try {
            // Parse property element.

            var oGEditRes = ITHit.XPath.evaluate('/d:prop/ithit:gpreview', oProp.Value, oResolver);
            if ((oNode = oGEditRes.iterateNext())) {
                this.GFileID = oNode.firstChild().nodeValue();
            }

            // Exception had happened.
        } catch (e) {
            throw new ITHit.WebDAV.Client.Exceptions.PropertyException(
                ITHit.Phrases.Exceptions.ParsingPropertiesException,
                this.Href,
                oProp.Name,
                null,
                ITHit.WebDAV.Client.HttpStatus.OK,
                e
            );
        }
    }


});

;
(function () {

    /**
	 * This class provides methods for opening documents for editing directly from server and saving back to server
	 * without download and upload steps. This includes editing Microsoft Office documents as well as any other file
	 * types and works on Windows, Mac OS X and Linux.
	 * @api
	 * @class ITHit.WebDAV.Client.DocManager
	 */
    var self = ITHit.DefineClass('ITHit.WebDAV.Client.DocManager', null, {
        __static: /** @lends ITHit.WebDAV.Client.DocManager */{

            /**
			 * Collection of extensions of files which are opened with Microsoft Office.
			 * @api
			 * @type {ITHit.WebDAV.Client.MsOfficeEditExtensions}
			 * @examplecode ITHit.WebDAV.Client.Tests.DocManager.MsOfficeEditExtensions.EditDocumentTest
			 */
            MsOfficeEditExtensions: ITHit.WebDAV.Client.MsOfficeEditExtensions,

            /**
			 * Timeout in milliseconds to call error callback if application associated with the extension did not start.
			 * Default is 3000ms.
			 * Used in Chrome / Internet Explorer / Safari if protocol application is not installed AND web browser protocol warning dialog is disabled AND EditDocument() / MicrosoftOfficeEditDocument() function is called (in case of Basic/Digest/Anonymous authentication).
			 * NOT used in Firefox / Edge OR if DavProtocolEditDocument() is called OR if web browser protocol warning dialog is enabled.
			 * @api
			 * @type {ITHit.WebDAV.Client.ProtocolTimeoutMs}
			 */
            ProtocolTimeoutMs: 3000,

            ObsoleteMessage: function (funcName) {
                if (confirm(funcName + " function is deprecated.\n\nSee how to upgrade here:\nhttp://www.webdavsystem.com/ajax/programming/upgrade\n\nSelect OK to navigate to the above URL.\n")) {
                    window.open("http://www.webdavsystem.com/ajax/programming/upgrade", "_blank");
                }
            },

            /* Obsolete. Implementation provided for backward compatibility with v1.x. */
            JavaEditDocument: function (sDocumentUrl, sMountUrl, sJavaAppletUrl, oContainer) {
                self.ObsoleteMessage("DocManager.JavaEditDocument()");

                // get plugins folder location from jar file URL
                var pluginsFolder = sJavaAppletUrl != null ? self.GetFolder(sJavaAppletUrl) : null;
                var errorCallback = self.GetDefaultCallback(pluginsFolder);

                this.DavProtocolEditDocument(sDocumentUrl, sMountUrl, errorCallback);
            },

            /* Obsolete. Implementation provided for backward compatibility with v1.x. */
            JavaOpenFolderInOsFileManager: function (sFolderUrl, sMountUrl, sJavaAppletUrl, oContainer) {
                self.ObsoleteMessage("DocManager.JavaOpenFolderInOsFileManager()");

                // get plugins folder location from jar file URL
                var pluginsFolder = sJavaAppletUrl != null ? self.GetFolder(sJavaAppletUrl) : null;
                var errorCallback = self.GetDefaultCallback(pluginsFolder);

                this.DavProtocolOpenFolderInOsFileManager(sDocumentUrl, sMountUrl, errorCallback);
            },

            /* Obsolete. Implementation provided for backward compatibility with v1.x. */
            IsMicrosoftOfficeAvailable: function () {
                alert("The DocManager.IsMicrosoftOfficeAvailable() function is deprecated. See http://www.webdavsystem.com/ajax/programming/upgrade for more details.");
                return true; // return true for beackward compatibility. Typically this call is used in combination with IsMicrosoftOfficeDocument()
            },

            /* Obsolete. Implementation provided for backward compatibility with v1.x. */
            GetMsOfficeVersion: function () {
                self.ObsoleteMessage("DocManager.GetMsOfficeVersion()");
                return null;
            },

            /* Obsolete. Implementation provided for backward compatibility with v1.x. */
            ShowMicrosoftOfficeWarning: function () {
                alert("The DocManager.ShowMicrosoftOfficeWarning() function is deprecated. See http://www.webdavsystem.com/ajax/programming/upgrade for more details.");
            },

            /**
			 * Gets file name of the protocol installer depending on OS.
			 * @private
             * @return {string} File name of the protocol installer.
			 * @deprecated Please use <code>GetProtocolInstallFileNames</code> instead
			 */
            GetInstallFileName: function () {
                var fileName = "ITHitEditDocumentOpener.";
                var ext;
                switch (ITHit.DetectOS.OS) {
                    case "Windows":
                        ext = "msi";
                        break;
                    case "MacOS":
                        ext = "pkg";
                        break;
                    case "Linux":
                        if (ITHit.DetectDevice.Android) {
                            ext = null;
                            break;
                        }
                    case "UNIX":
                        ext = "deb";
                        break;
                    default:
                        ext = null;
                }
                return ext != null ? (fileName + ext) : null;
            },

            /**
			 * Gets file names of the protocol installer depending on OS.
			 * @api
             * @return {Array} An array with file names of the protocol installer.
			 */
            GetProtocolInstallFileNames: function () {
                var fileName = "ITHitEditDocumentOpener";
                var array = [];
                switch (ITHit.DetectOS.OS) {
                    case "Windows":
                        array.push(fileName + ".msi");
                        break;
                    case "MacOS":
                        array.push(fileName + ".pkg");
                        break;
                    case "Linux":
                        array.push(fileName + ".deb");
                        array.push(fileName + ".rpm");
                        break;
                    case "UNIX":
                        array.push(fileName + ".deb");
                        break;
                    default:
                        break;
                }
                return array;
            },

            /**
            * Returns true if protocol application installer is supported for the OS on which this function is called, false - otherwise.
            * @api
            * @return {boolean} True if protocol application installer is supported for the OS on which this function is called.
            */
            IsDavProtocolSupported: function () {
                return this.GetInstallFileName() != null;
            },

            /**
            * @Deprecated This function will be deleted in the next releases. Update your code replacing IsDavProtocoSupported() with IsDavProtocolSupported() 
            */
            IsDavProtocoSupported: function () {
                alert("Function IsDavProtocoSupported() is deprecated and will be deleted in the next releases. Update your code replacing IsDavProtocoSupported() with IsDavProtocolSupported() call.");
                return this.IsDavProtocolSupported();
            },

            /**
			 * <p>Mounts folder in file system and opens it in default OS file manger. Requests protocol installation if folder opening protocol is not installed.</p>
             * <i class="optional">The following functionality is supported in v3 Beta and later only:</i>
             * <p>
             * This function supports both challenge-response authentication (Basic, Digest, NTLM, Kerberos) and cookies authentication.
             * If <code>'None'</code> is specified in the <code>sSearchIn</code> parameter the challenge-response authentication is used, otherwise cookies authentication is used.
             * </p>
			 * @api
			 * @param {string} sFolderUrl URL of the folder to open in OS file manager. Must be a full URL including the domain name.
             * @param {string} [sMountUrl] URL to mount file system to before opening the folder. Usually this is your WebDAV server root folder. If this parameter is not specified file system will be mounted to the folder in which document is located.
			 * @param {function} [errorCallback] Function to call if file manager opening has failed. Typically you will request the protocol installation in this callback.
             * If not specified a default message offering protocol installation will be displayed.
             * @param {string} [reserved] Reserved for future use.
             * @param {string} [sSearchIn] <span class="optional">v3 Beta and later only.</span> Indicates cookies authentication. Allowed values are:
             * <ul>
             * <li><code>'Current'</code> - Copies cookies from web browser in which this script is running.</li>
             * <li><code>'None'</code> - do not search or copy any cookies.</li>
             * </ul>
             * Default is <code>'None'</code>.
             * @param {string} [sCookieNames] <span class="optional">v3 Beta and later only.</span> Coma separated list of cookie names to search for. Microsoft Office requires persistent cookie (with expiration date), it does not support session cookies.
             * @param {string} [sLoginUrl] <span class="optional">v3 Beta and later only.</span> Login URL to redirect to in case any cookies specified in <code>sCookieNames</code> parameter are not found.
			 */
            OpenFolderInOsFileManager: function (sFolderUrl, sMountUrl, errorCallback, oContainer, sSearchIn, sCookieNames, sLoginUrl) {

                if (oContainer == null)
                    oContainer = window.document.body;

                // Open using HttpBehavior component.
                if (ITHit.DetectBrowser.IE && (ITHit.DetectBrowser.IE < 11)) {

                    if (oContainer._httpFolder == null) {
                        var span = {
                            nodeName: 'span',
                            style: { display: 'none', behavior: 'url(#default#httpFolder)' }
                        };
                        oContainer._httpFolder = ITHit.Utils.CreateDOMElement(span);
                        oContainer.appendChild(oContainer._httpFolder);
                    }

                    var res = oContainer._httpFolder.navigate(sFolderUrl);
                    //return res == "OK";


                } else {
                    // Open folder using custom protocol.

                    var pluginsFolder = null;

                    // If errorCallback is a .jar file url this is a v1.x code call.
                    if ((typeof (errorCallback) == 'string') && (self.GetExtension(errorCallback) == "jar")) {
                        // recommend to upgrade
                        if (confirm("The DocManager.OpenFolderInOsFileManager() function signature changed.\n\nSee how to upgrade here:\nhttp://www.webdavsystem.com/ajax/programming/upgrade\n\nSelect OK to navigate to the above URL.\n")) {
                            window.open("http://www.webdavsystem.com/ajax/programming/upgrade", "_blank");
                        }

                        // get plugins folder location from jar file URL
                        pluginsFolder = self.GetFolder(errorCallback);

                        errorCallback = null;
                    }

                    if (errorCallback == null) {
                        errorCallback = self.GetDefaultCallback(pluginsFolder);
                    }

                    sFolderUrl = sFolderUrl.replace(/\/?$/, '/'); // add trailing slash if not present

                    this.OpenDavProtocol(sFolderUrl, sMountUrl, errorCallback, null, sSearchIn, sCookieNames, sLoginUrl);
                }
            },

            GetExtension: function (sDocumentUrl) {
                var queryIndex = sDocumentUrl.indexOf("?");
                if (queryIndex > -1) {
                    sDocumentUrl = sDocumentUrl.substr(0, queryIndex);
                }

                var aExt = sDocumentUrl.split(".");
                if (aExt.length === 1) {
                    return "";
                }
                return aExt.pop();
            },

            // get plugins folder location from jar file URL
            GetFolder: function (sUrl) {
                var queryIndex = sUrl.indexOf("?");
                if (queryIndex > -1) {
                    sUrl = sUrl.substr(0, queryIndex);
                }

                return sUrl.substring(0, sUrl.lastIndexOf("/")) + "/";
            },

            /**
			 * Extracts extension and returns true if URL points to Microsoft Office Document.
			 * @api
			 * @param {string} sDocumentUrl URL of the document.
			 * @return {boolean} True if URL points to Microsoft Office Document.
			 */
            IsMicrosoftOfficeDocument: function (sDocumentUrl) {
                var ext = self.GetExtension(ITHit.Trim(sDocumentUrl));
                if (ext === "") {
                    return false;
                }

                return self.GetMsOfficeSchemaByExtension(ext) !== '';
            },

            /**
			 *
			 * @param sExt
			 * @returns {string}
			 */
            GetMsOfficeSchemaByExtension: function (sExt) {
                var result = self.MsOfficeEditExtensions.GetSchema(sExt);
                return result === null ? '' : result;
            },

            /**
			 * Opens Microsoft Office document using protocol. This method does not offer protocol installation if protocol is not found. Microsoft Office must be installed on a client machine.
			 * @api
			 * @param {string} sDocumentUrl URL of the document to edit. This must be a Microsoft Office document. Must be a full URL including the domain name.
			 */
            MicrosoftOfficeEditDocument: function (sDocumentUrl, errorCallback) {
                sDocumentUrl = ITHit.Trim(sDocumentUrl);

                var ext = self.GetExtension(sDocumentUrl);
                if (ext === "" && errorCallback != undefined) {
                    self.CallErrorCallback(errorCallback);
                }
                else {
                    if (86 <= ITHit.DetectBrowser.Chrome || 82 <= ITHit.DetectBrowser.FF){
                        console.log('Function MicrosoftOfficeEditDocument() does not support errorCallback parameter');
                    }
                    var command = (ITHit.DetectOS.OS == 'MacOS') ? encodeURIComponent('ofe|u|') : 'ofe|u|';
                    this.OpenProtocol(self.GetMsOfficeSchemaByExtension(ext) + ':' + command + sDocumentUrl, errorCallback);
                }
            },

            FileFormats: {

                ProtectedExtentions: [/*'ace', 'ade', 'adp', 'adt', 'app', 'asp', 'arj', 'asd', 'bas', 'bat', 'bin', 'btm', 'cbt', 'ceo', 'chm', 'cmd', 'cla', 'com', 'cpl', 'crt', 'csc', 'css', 'dll', 'drv', 'exe', 'email', 'fon', 'hlp', 'hta', 'htm', 'inf', 'ins', 'isp', 'je', 'js', 'lib', 'lnk', 'mdb', 'mde', 'mht', 'msc', 'msi', 'mso', 'msp', 'mst', 'obj', 'ocx', 'ov', 'pcd', 'pgm', 'pif', 'prc', 'rar', 'reg', 'scr', 'sct', 'shb', 'shs', 'smm', 'swf', 'sys', 'tar', 'url', 'vb', 'vxd', 'wsc', 'wsf', 'wsh', '{'*/]
            },

            GetDefaultCallback: function (pluginsFolder) {
                if (pluginsFolder == null)
                    pluginsFolder = "/Plugins/";

                var errorCallback = function () {
                    if (confirm('To open document you must install a custom protocol. Continue?')) {
                        window.open(pluginsFolder + self.GetInstallFileName());
                    }
                };
                return errorCallback;
            },

            CallErrorCallback: function (errorCallback) {
                if (errorCallback == null) {
                    errorCallback = self.GetDefaultCallback(null);
                }
                errorCallback();
            },

            /**
			 * <p>Opens document for editing. In case of Microsoft Office documents, it will try to use Microsoft Office protocols first.
             * If Microsoft Office protocols are not found it will use davX: protocol and prompt to install it if not found.</p>
             * <p>This function supports only challenge-response authentication (Basic, Digest, NTLM, Kerberos).
             * You can also use it to open MS Office documents from servers with MS-OFBA authentication.</p>
             * <p>This function does <b>NOT</b> support cookies authentication. If your server is using cookies authentication use the <code>DavProtocolEditDocument()</code> function instead.</p>
			 * @example
			 * &lt;!DOCTYPE html&gt;
			 * &lt;html&gt;
			 * &lt;head&gt;
			 *     &lt;meta charset="utf-8" /&gt;
			 *     &lt;script type="text/javascript" src="ITHitWebDAVClient.js" &gt;&lt;/script&gt;
			 * &lt;/head&gt;

			 * &lt;body&gt;
			 * &lt;script type="text/javascript"&gt;
			 *     function edit() {
			 *         ITHit.WebDAV.Client.DocManager.EditDocument("http://localhost:87654/folder/file.ext", "http://localhost:87654/", errorCallback);
			 *     }
			 *
			 *     function errorCallback() {
			 *         var installerFilePath = "/Plugins/" + ITHit.WebDAV.Client.DocManager.GetProtocolInstallFileNames()[0];
             *
			 *         if (confirm("Opening this type of file requires a protocol installation. Select OK to download the protocol installer.")){
			 *             window.open(installerFilePath);
			 *         }
			 *     }
			 * &lt;/script&gt;
			 * &lt;input type="button" value="Edit Document" onclick="edit()" /&gt;
			 * &lt;/body&gt;
			 * &lt;/html&gt;
			 * @api
			 * @param {string} sDocumentUrl URL of the document to open for editing from server. Must be a full URL including the domain name. Unlike <code>DavProtocolEditDocument()</code> function, this function supports only one document URL in this parameter.
             * @param {string} [sMountUrl] URL to mount file system to before opening the folder. Usually this is your WebDAV server root folder. If this perameter is not specified file system will be mounted to the folder in which document is located.
			 * @param {function} [errorCallback] Function to call if document opening failed. Typically you will request the protocol installation in this callback. This callback is executed for non-Microsoft Office documents only.
             * If not specified a default message offering protocol installation will be displayed.      
			 */
            EditDocument: function (sDocumentUrl, sMountUrl, errorCallback) {

                var pluginsFolder = null;
                // If second param is a .jar file url this is a v1.x code call.
                if ((typeof (sMountUrl) == 'string') && (self.GetExtension(sMountUrl) == "jar")) {
                    // recommend to upgrade
                    if (confirm("The DocManager.EditDocument() function signature changed.\n\nSee how to upgrade here:\nhttp://www.webdavsystem.com/ajax/programming/upgrade\n\nSelect OK to navigate to the above URL.\n")) {
                        window.open("http://www.webdavsystem.com/ajax/programming/upgrade", "_blank");
                    }

                    // get plugins folder location from jar file URL
                    pluginsFolder = self.GetFolder(sMountUrl);

                    sMountUrl = null;
                }

                if (errorCallback == null) {
                    errorCallback = self.GetDefaultCallback(pluginsFolder);
                }

                if (ITHit.DetectBrowser.Chrome /*|| ITHit.DetectBrowser.Safari*/) { // commented as Safari does not support extension 
                    self.EditDocumentIntegrated(sDocumentUrl, sMountUrl, errorCallback);
                    return;
                }

                // Edit MS Office document with Microsoft Office, if failed use custom protocol
                // MS Office is available on Windows and OS X only, no need to try opening with MS Office protocols on Linux 		
                if (self.IsMicrosoftOfficeDocument(sDocumentUrl) && ((ITHit.DetectOS.OS == 'Windows') || (ITHit.DetectOS.OS == 'MacOS') || (ITHit.DetectOS.OS == 'IOS'))) {

                    self.MicrosoftOfficeEditDocument(sDocumentUrl, function () {
                        self.DavProtocolEditDocument(sDocumentUrl, sMountUrl, errorCallback);
                    });
                }
                else {
                    this.DavProtocolEditDocument(sDocumentUrl, sMountUrl, errorCallback);
                }
            },

            /**
			 * Extracts extension and returns true if the document can be edited in G Suite editor or document preview generated via G Suite.
			 * @api
			 * @param {string} sDocumentUrl URL of the document.
			 * @return {boolean} True if URL points to GSuite Editor.
			 */
            IsGSuiteDocument: function (sDocumentUrl) {
                var ext = self.GetExtension(ITHit.Trim(sDocumentUrl));
                if (ext === "") {
                    return false;
                }

                return ['docx', 'pptx', 'xlsx', 'rtf'].indexOf(ext) != -1;
            },

            /**
			 * <p>Edit MS Office document with G Suite Online Editor.</p>             
             * @api
             * @param {string} sDocumentUrl URL of the document to open for editing from server. Must be a full URL including the domain name.
             * @param {DOM} oContainerDomElement HTML DOM element where the G Suite online editor will be loaded. If this parameter is omitted or null is passed the editor will be created in a new tab/window.
			 * @param {function} [errorCallback] Function to call if document opening failed.
            */
            GSuiteEditDocument: function (sDocumentUrl, oContainerDomElement, errorCallback) {
                if (self.IsGSuiteDocument(sDocumentUrl)) {
                    var lockTimeOut = 1800; // in seconds
                    var webDavSession = new ITHit.WebDAV.Client.WebDavSession();

                    // check if oContainerDomElement is null before make ajax call
                    if (!oContainerDomElement) {
                        oContainerDomElement = window.open('', '', 'directories=0,titlebar=0,toolbar=0,location=0,status=0,menubar=0,scrollbars=0,resizable=0,width=' + window.innerWidth + ',height=' + window.innerHeight);
                    }

                    webDavSession.GEditAsync(sDocumentUrl, 1800, function (oAsyncResult) {
                        var webDavSession = new ITHit.WebDAV.Client.WebDavSession();
                        var oEditorClosed = false;
                        var oGEditInfo = oAsyncResult.Result;

                        if (oAsyncResult.IsSuccess) {

                            function _unlockFile() {
                                if (!oEditorClosed) {
                                    oEditorClosed = true;
                                    webDavSession.GUnlock(sDocumentUrl, oGEditInfo.LockToken.LockToken, oGEditInfo.GRevisionID);
                                }
                            }

                            function _refreshFileLock(fCallback) {
                                var oRequest = webDavSession.CreateRequest(this.__className + '.RefreshLockAsync()');

                                ITHit.WebDAV.Client.Methods.LockRefresh.GoAsync(
                                    oRequest,
                                    sDocumentUrl,
                                    lockTimeOut,
                                    oGEditInfo.LockToken.LockToken,
                                    null,
                                    function (oAsyncResult) {
                                        if (oAsyncResult.IsSuccess) {
                                            oAsyncResult.Result = oAsyncResult.Result.LockInfo;
                                            fCallback(oAsyncResult);
                                        }

                                        oRequest.MarkFinish();
                                    }
                                );
                            }

                            function _refreshFileLockByTimeout() {
                                setTimeout(function () {
                                    if (!oEditorClosed) {
                                        _refreshFileLock(function () {
                                            _refreshFileLockByTimeout();
                                        });
                                    }
                                }, (lockTimeOut - 10) * 1000);
                            }

                            // refresh lock by timeout
                            _refreshFileLockByTimeout();

                            // create google editor
                            self.CreateGSuiteEditorContainer('https://docs.google.com/' + self.GetGSuiteEditorName(sDocumentUrl) + '/d/' + oGEditInfo.GFileID + '/edit?usp=sharing', oContainerDomElement, function () {
                                _unlockFile();
                            });
                        } else if (errorCallback) {
                            errorCallback(oAsyncResult.Error);
                        }
                    });

                }
                else {
                    alert('Only GSuite documents are supported.');
                }
            },

            /**
			 * <p>Preview MS Office document with G Suite Online Tool.</p>             
             * @api
             * @param {string} sDocumentUrl URL of the document to open for preview. Must be a full URL including the domain name.
             * @param {DOM} oContainerDomElement HTML DOM element where the G Suite preview will be loaded. If this parameter is omitted or null is passed the preview will be created in a new tab/window.
			 * @param {function} [errorCallback] Function to call if document opening failed.
            */
            GSuitePreviewDocument: function (sDocumentUrl, oContainerDomElement, errorCallback) {
                var webDavSession = new ITHit.WebDAV.Client.WebDavSession();

                // check if oContainerDomElement is null before make ajax call
                if (!oContainerDomElement) {
                    oContainerDomElement = window.open('', '', 'directories=0,titlebar=0,toolbar=0,location=0,status=0,menubar=0,scrollbars=0,resizable=0,width=' + window.innerWidth + ',height=' + window.innerHeight);
                }

                var oRequest = webDavSession.CreateRequest('DocManager.GPreviewAsync()');
                ITHit.WebDAV.Client.Methods.GPreview.GoAsync(
                    oRequest,
                    sDocumentUrl,
                    function (oAsyncResult) {
                        if (oAsyncResult.IsSuccess) {
                            // create google preview editor
                            self.CreateGSuiteEditorContainer('https://drive.google.com/file/d/' + oAsyncResult.Result.GFileID + '/preview', oContainerDomElement, function () {
                                ITHit.WebDAV.Client.Methods.GRemovePreview.GoAsync(webDavSession.CreateRequest('DocManager.GRemovePreviewAsync()'), sDocumentUrl, function () { });
                            });
                        }
                        else if (errorCallback) {
                            errorCallback(oAsyncResult.Error);
                        }

                        oRequest.MarkFinish();
                    }
                );
            },

            /**
             * @private
            */
            CreateGSuiteEditorContainer: function (oGSuiteEditorUrl, oContainerDomElement, onbeforeunloadCallback) {
                // create google editor
                var mainIframeEditor = null;
                var oContainerDomElementIsIframe = false;

                // insert main iframe
                if (oContainerDomElement.document) {
                    mainIframeEditor = oContainerDomElement.document.createElement("iframe");
                }
                else {
                    mainIframeEditor = document.createElement('iframe');
                    oContainerDomElementIsIframe = true;
                }
                mainIframeEditor.style.width = '100%';
                mainIframeEditor.style.height = '100%';
                mainIframeEditor.style.border = 'none';
                mainIframeEditor.focus();

                mainIframeEditor.onload = function () {
                    // insert G suite editor iframe
                    var gIframeEditor = mainIframeEditor.contentWindow.document.createElement('iframe');
                    gIframeEditor.setAttribute('src', oGSuiteEditorUrl);
                    gIframeEditor.style.width = '100%';
                    gIframeEditor.style.height = '100%';
                    gIframeEditor.style.border = 'none';
                    if (oContainerDomElementIsIframe) {
                        mainIframeEditor.contentWindow.onunload = function () {
                            onbeforeunloadCallback();
                        };
                    }
                    else {
                        mainIframeEditor.contentWindow.onbeforeunload = function () {
                            onbeforeunloadCallback();
                        };
                    }

                    mainIframeEditor.contentWindow.document.body.appendChild(gIframeEditor);
                }

                if (oContainerDomElement.document) {
                    oContainerDomElement.document.body.appendChild(mainIframeEditor);
                }
                else {
                    oContainerDomElement.appendChild(mainIframeEditor);
                }
            },

            /**
			 * @private
			*/
            GetGSuiteEditorName: function (sDocumentUrl) {
                var editorName = 'viewer';
                switch (self.GetExtension(sDocumentUrl)) {
                    case 'rtf':
                    case 'doc':
                    case 'docx':
                        editorName = 'document';
                        break;
                    case 'xls':
                    case 'xlsx':
                        editorName = 'spreadsheets';
                        break;
                    case 'ppt':
                    case 'pptx':
                        editorName = 'presentation';
                        break;
                }

                return editorName;
            },

            /**
			 * @private
			 */
            EditDocumentIntegrated: function (sDocumentUrl, sMountUrl, errorCallback) {
                if (this.IsExtensionInstalled()) {
                    if (self.IsMicrosoftOfficeDocument(sDocumentUrl)) {
                        var ext = self.GetExtension(sDocumentUrl);
                        self.IsProtocolAvailableAsync(ext,
                            function (oAsyncResult) {
                                if (oAsyncResult.IsSuccess && oAsyncResult.Result) {
                                    self.MicrosoftOfficeEditDocument(sDocumentUrl);
                                } else {
                                    self.DavProtocolEditDocument(sDocumentUrl, sMountUrl, errorCallback);
                                }
                            });
                    } else {
                        self.DavProtocolEditDocument(sDocumentUrl, sMountUrl, errorCallback);
                    }
                }
                else {
                    if (self.IsMicrosoftOfficeDocument(sDocumentUrl)) {
                        self.MicrosoftOfficeEditDocument(sDocumentUrl, errorCallback);
                    }
                    else {
                        self.CallErrorCallback(errorCallback);
                    }
                }
            },

            /**
			 * This function get protocol version asynchronously.
			 * @param {ITHit.WebDAV.Client.DocManager~GetDavProtocolAppVersionAsyncCallback} fCallback Function to call when operation is completed.
			 */
            GetDavProtocolAppVersionAsync: function (fCallback) {
                ITHit.WebDAV.Client.BrowserExtension.GetDavProtocolAppVersionAsync(fCallback);
            },

            /**
             * This function check if extension installed.
             * @return {boolean}
             */
            IsExtensionInstalled: function () {
                return ITHit.WebDAV.Client.BrowserExtension.IsExtensionInstalled(true);
            },

            /**
             * This function check if extension installed.
			 * @param isMajorVersionCheck If we didn't find protocol name in data tag, then check major version for protocol name
             * @return {boolean}
             */
            IsExtensionInstalled: function (isMajorVersionCheck) {
                return ITHit.WebDAV.Client.BrowserExtension.IsExtensionInstalled(isMajorVersionCheck);
            },

            /**
			 * This function check if Office URI Scheme installed for file extension.
			 * If browser extension does not fill data in <code>'_Timeout'</code>, or error occurred <code>'successCallback'</code> called with false.
			 * @param {string} [sExt] File extension.
			 * @param {ITHit.WebDAV.Client.DocManager~IsProtocolAvailableAsyncCallback} fCallback Function to call when operation is completed.
			 */
            IsProtocolAvailableAsync: function (sExt, fCallback) {
                ITHit.WebDAV.Client.BrowserExtension.IsProtocolAvailableAsync(sExt, fCallback);
            },


            /**
			 * <p>Opens document for editing or printing using davX: protocol and prompts to install the protocol it if not found.</p>
             * <i class="optional">The following functionality is supported in v3 Beta and later only:</i>
             * <p>
             * This function supports both challenge-response authentication (Basic, Digest, NTLM, Kerberos) and cookies authentication.
             * If <code>'None'</code> is specified in the <code>sSearchIn</code> parameter the challenge-response authentication is used, otherwise cookies authentication is used.
             * </p>
             * @example
			 * &lt;!DOCTYPE html&gt;
			 * &lt;html&gt;
			 * &lt;head&gt;
			 *     &lt;meta charset="utf-8" /&gt;
			 *     &lt;script type="text/javascript" src="ITHitWebDAVClient.js" &gt;&lt;/script&gt;
			 * &lt;/head&gt;
			 * &lt;body&gt;
			 * &lt;script type="text/javascript"&gt;
			 *     function edit() {
			 *         ITHit.WebDAV.Client.DocManager.DavProtocolEditDocument(
			 *             'http://localhost:87654/folder/file.ext', // Document URL(s)
			 *             'http://localhost:87654/',                // Mount URL
			 *             errorCallback,                            // Function to call if protocol app is not installed
			 *             null,                                     // Reserved
			 *             'Current',                                // Which browser to copy cookies from: 'Current', 'None'
			 *             '.AspNet.ApplicationCookie',              // Cookie(s) to copy.
			 *             '/Account/Login',                         // URL to navigate to if any cookie from the list is not found.
			 *             'Edit'                                    // Command to execute: 'Edit', 'OpenWith', 'Print'
			 *         );
			 *     }
			 *
			 *     function errorCallback() {
			 *         var installerFilePath = "/Plugins/" + ITHit.WebDAV.Client.DocManager.GetProtocolInstallFileNames()[0];
			 *
			 *         if (confirm("Opening this type of file requires a protocol installation. Select OK to download the protocol installer.")){
			 *             window.open(installerFilePath);
			 *         }
			 *     }
			 * &lt;/script&gt;
			 * &lt;input type="button" value="Edit Document" onclick="edit()" /&gt;
			 * &lt;/body&gt;
			 * &lt;/html&gt;
			 * @api
			 * @param {string} sDocumentUrls Array of document URLs to be opened for editing from server. All documents must be located under the same mount URL (specified in <code>sMountUrl</code> parameter). Must be a full URL(s) including the domain name.
             * @param {string} [sMountUrl] URL to mount file system to before opening the folder. Usually this is your WebDAV server root folder. If this perameter is not specified file system will be mounted to the folder in which document is located.
			 * @param {function} [errorCallback] Function to call if document opening failed. Typically you will request the protocol installation in this callback.
             * If not specified a default message offering protocol installation will be displayed.
             * @param {string} [reserved] Reserved for future use.
             * @param {string} [sSearchIn] <span class="optional">v3 Beta and later only.</span> Indicates cookies authentication. Supported options are:
             * <ul>
             * <li><code>'Current'</code> - Copies cookies from web browser in which this script is running.</li>
             * <li><code>'None'</code> - do not search or copy any cookies.</li>
             * </ul>
             * Default is <code>'None'</code>.
             * @param {string} [sCookieNames] <span class="optional">v3 Beta and later only.</span> Coma separated list of cookie names to search for. Microsoft Office requires persistent cookie (with expiration date), it does not support session cookies.
             * @param {string} [sLoginUrl] <span class="optional">v3 Beta and later only.</span> Login URL to redirect to in case any cookies specified in <code>sCookieNames</code> parameter are not found.
             * @param {string} [sCommand] <span class="optional">v3 Beta and later only.</span> Command to use when opening the document. Supported options are:
             * <ul>
             * <li> <code>null</code> - Chooses an appropriate verb to open a document in the associated application.
             * <li> <code>'Edit'</code> - Opens a document for editing.
             * <li> <code>'Open'</code> - Opens a document in the associated application. Not applicable for some applications.
             * <li> <code>'OpenWith'</code> - Show system 'Open With' dialog to select application to be used to open a document. This option is supported on Windows only.
             * <li> <code>'Print'</code> - Prints a document. The application that prints a document is running in a minimized state and automatically closes if printing is successful. If printing fails, the application remains open. To print multiple documents, pass a list of documents as a first parameter. This option is supported on Windows only.
             * </ul>
             * Default is <code>null</code>.       
			 */

            DavProtocolEditDocument: function (sDocumentUrls, sMountUrl, errorCallback, sReserved, sSearchIn, sCookieNames, sLoginUrl, sCommand) {
                if (sCommand !== null && sCommand == 'Print') {
                    self.GetDavProtocolAppVersionAsync(function (oAsyncResult) {
                        if (oAsyncResult.IsSuccess && ITHit.WebDAV.Client.Version.VersionCompare(oAsyncResult.Result, '5.11') < 0) {
                            if (confirm('Protocol application v5.11 or later is required.\n\nDownload the latest protocol application?')) {
                                self.CallErrorCallback(errorCallback);
                            }
                        } else {
                            internalDavProtocolEditDocument(sDocumentUrls, sMountUrl, errorCallback, sReserved, sSearchIn, sCookieNames, sLoginUrl, sCommand);
                        }
                    });
                } else {
                    internalDavProtocolEditDocument(sDocumentUrls, sMountUrl, errorCallback, sReserved, sSearchIn, sCookieNames, sLoginUrl, sCommand);
                }

                function internalDavProtocolEditDocument(sDocumentUrls, sMountUrl, errorCallback, sReserved, sSearchIn, sCookieNames, sLoginUrl, sCommand) {
                    if (Array.isArray(sDocumentUrls))
                        sDocumentUrls = JSON.stringify(sDocumentUrls)

                    self.OpenDavProtocol(sDocumentUrls, sMountUrl, errorCallback, sReserved, sSearchIn, sCookieNames, sLoginUrl, sCommand);
                }
            },

            DavProtocolOpenFolderInOsFileManager: function (sFolderUrl, sMountUrl, errorCallback, sReserved, sSearchIn, sCookieNames, sLoginUrl, sCommand) {
                sFolderUrl = sFolderUrl.replace(/\/?$/, '/'); // add trailing slash if not present
                this.OpenDavProtocol(sFolderUrl, sMountUrl, errorCallback, sReserved, sSearchIn, sCookieNames, sLoginUrl, sCommand);
            },
            
            CheckExtensionInstalledAndThrowErrorCallback: function(errorCallback){
                //let Chrome error callback works when protocol on the site and the installed one do not match within the same major version. Because Chrome don't have a function to open url with error callback
                if (!this.IsExtensionInstalled(!ITHit.DetectBrowser.Chrome) && !ITHit.DetectBrowser.Edge && !ITHit.DetectBrowser.IE) {
                    self.CallErrorCallback(errorCallback);
                    return false;
                }
                return true;
            },

            OpenDavProtocol: function (sUrl, sMountUrl, errorCallback, sReserved, sSearchIn, sCookieNames, sLoginUrl, sCommand) {
               
                var params = new Array(),
					msOfficeSchema = self.MsOfficeEditExtensions.GetSchema(self.GetExtension(sUrl));
                params.push('ItemUrl=' + encodeURIComponent(ITHit.Trim(sUrl)));
                if (sMountUrl != null)
                    params.push('MountUrl=' + ITHit.Trim(sMountUrl));
                params.push('Browser=' + ITHit.DetectBrowser.Browser);
                sSearchIn = ITHit.WebDAV.Client.WebDavUtil.NormalizeEmptyOrNoneToNull(sSearchIn);
                if (sSearchIn != null)
                    params.push('SearchIn=' + ITHit.Trim(sSearchIn));
                sCookieNames = ITHit.WebDAV.Client.WebDavUtil.NormalizeEmptyToNull(sCookieNames);
                if (sCookieNames != null)
                    params.push('CookieNames=' + ITHit.Trim(sCookieNames));
                sLoginUrl = ITHit.WebDAV.Client.WebDavUtil.NormalizeEmptyToNull(sLoginUrl);
                if (sLoginUrl != null)
                    params.push('LoginUrl=' + ITHit.Trim(sLoginUrl));
                if (sCommand != null)
                    params.push('Command=' + ITHit.Trim(sCommand));
                if (msOfficeSchema != null)
                    params.push('MsOfficeSchema=' + msOfficeSchema);

                if(sSearchIn == null && ITHit.DetectBrowser.Safari){
                    // on Safari open docs should work without extension for non cookies auth
                }
                else if(!this.CheckExtensionInstalledAndThrowErrorCallback(errorCallback)) return;

                var uri = ITHit.WebDAV.Client.DavConstants.ProtocolName + ':' + params.join(';'); // if URI contains '|' links doeas not work in Chrome on OS X

                //var uri = params.map(function(elem){for(i in elem){return i+'='+elem[i];}}).join(';');
                //var uri = Object.getOwnPropertyNames(params).map(function(key){return key+'='+params[key]}).join(',');

                // Chrome on OS X does not open protocol link if it contains spaces
                if (ITHit.DetectBrowser.Chrome && (ITHit.DetectOS.OS == 'MacOS')) {
                    uri = uri.split(' ').join('%20');
                }

                // If Chrome or Edge or Firefox and in windows call new function with cookies OpenProtocolWithCookies
                if ((sSearchIn != null) && (ITHit.DetectBrowser.Chrome || ITHit.DetectBrowser.Edge || ITHit.DetectBrowser.FF)) {
                    self.OpenProtocolWithCookies(uri, errorCallback);
                } else {
                    self.OpenProtocol(uri, errorCallback);
                }
            },
            
            /*
            // All params in dic are mandatory.
            var dParams = { itemUrl:['url1', 'url2'], 
                        userId:'', 
                        userEmail:'', 
                        siteId:'',
                        webId:'',
                        webTitle:'',
                        webUrl:'',
                        listId:'',
                        listTitle:'',
                        rootUrl:'https://ithitdemo.sharepoint.com/Shared%20Documents'
                      };
                      
            var dParams = { itemUrl:['https://ithitdemo.sharepoint.com/Shared Documents/test/sample.txt'], 
                        userId:'840b765b-f2f3-4a6d-92e5-7ad2c16eb928', 
                        userEmail:'dmytro.riabko@ithitdemo.onmicrosoft.com', 
                        siteId:'82a566c8-e534-449f-9cce-9cd4c4e9110c',
                        webId:'ab5a619b-ebb2-4cba-b7dd-2c6b0d9b3827',
                        webTitle:'Edit Any Document for SPS Demo',
                        webUrl:'https://ithitdemo.sharepoint.com',
                        listId:'1C8C77C4-70F5-4C28-8252-CF54C780F553',
                        listTitle:'Documents',
                        rootUrl:'https://ithitdemo.sharepoint.com/Shared%20Documents'
                      };
            */
            SPSOpenDocument: function (dParams, errorCallback) {
                //let Chrome error callback works when protocol on the site and the installed one do not match within the same major version. Because Chrome don't have a function to open url with error callback
                if (!this.IsExtensionInstalled(!ITHit.DetectBrowser.Chrome) && !ITHit.DetectBrowser.Edge && !ITHit.DetectBrowser.IE) {
                    self.CallErrorCallback(errorCallback);
                    return;
                }
                var mandatory = ['itemUrl', 'userId', 'userEmail', 'siteId', 'webId', 'webTitle', 'webUrl', 'listId', 'listTitle', 'rootUrl'];
                 for(var i in mandatory){
					var m = mandatory[i];
                    if (!(m in dParams)){
                        console.log('SPSOpenDocument: ' + m + ' property is missing in income dictionary. Skipping this func.');
                        return;
                    }
                 }
                
                dParams['itemUrl'] = JSON.stringify(dParams['itemUrl'])

                var params = new Array();
                for(var p in dParams)
                    if (dParams.hasOwnProperty(p)) {
                        params.push(p + "=" + encodeURIComponent(dParams[p]));
                    }


                var uri = ITHit.WebDAV.Client.DavConstants.ProtocolName + ':' + params.join(';'); // if URI contains '|' links doeas not work in Chrome on OS X

                // Chrome on OS X does not open protocol link if it contains spaces
                if (ITHit.DetectBrowser.Chrome && (ITHit.DetectOS.OS == 'MacOS')) {
                    uri = uri.split(' ').join('%20');
                }

                self.OpenProtocol(uri, errorCallback);
            },

            RegisterEvent: function (target, eventType, errorCallback) {
                if (target.addEventListener) {
                    target.addEventListener(eventType, errorCallback);
                    return {
                        remove: function () {
                            target.removeEventListener(eventType, errorCallback);
                        }
                    };
                } else {
                    target.attachEvent(eventType, errorCallback);
                    return {
                        remove: function () {
                            target.detachEvent(eventType, errorCallback);
                        }
                    };
                }
            },

            CreateHiddenFrame: function (target, uri) {
                var iframe = document.createElement("iframe");
                iframe.src = uri;
                iframe.id = "hiddenIframe";
                iframe.style.display = "none";
                target.appendChild(iframe);
                return iframe;
            },

            CreateHiddenLink: function (target, uri) {
                var link = document.createElement("a");
                link.href = uri;
                link.id = "hiddenLink";
                link.style.display = "none";
                target.appendChild(link);
                return link;
            },

            OpenUriWithHiddenFrame: function (uri, errorCallback) {
                var timeout = setTimeout(function () {
                    self.CallErrorCallback(errorCallback);
                    handler.remove();
                }, self.ProtocolTimeoutMs);

                var iframe = document.querySelector("#hiddenIframe");
                if (!iframe) {
                    iframe = this.CreateHiddenFrame(document.body, "about:blank");
                }

                var handler = this.RegisterEvent(window, "blur", onBlur);

                function onBlur() {
                    clearTimeout(timeout);
                    handler.remove();
                }

                iframe.contentWindow.location.href = uri;
            },


            OpenUriWithHiddenLink: function (uri, errorCallback) {
                var timeout = setTimeout(function () {
                    self.CallErrorCallback(errorCallback);
                    handler.remove();
                }, self.ProtocolTimeoutMs);

                var link = document.querySelector("#hiddenLink");
                if (!link) {
                    link = this.CreateHiddenLink(document.body, "about:blank");
                }

                var handler = this.RegisterEvent(window, "blur", onBlur);

                function onBlur() {
                    clearTimeout(timeout);
                    handler.remove();
                }

                link.href = uri;
                link.click();
            },

            OpenUriWithTimeout: function (uri, errorCallback) {
                var timeout = setTimeout(function () {
                    self.CallErrorCallback(errorCallback);
                    if (!handler)
                        handler.remove();
                }, self.ProtocolTimeoutMs);

                var handler = this.RegisterEvent(window, "blur", onBlur);

                function onBlur() {
                    clearTimeout(timeout);
                    handler.remove();
                }

                window.location = uri;
            },

            OpenUriUsingChrome: function (uri, errorCallback) {
                if (86 <= ITHit.DetectBrowser.Chrome){
                    window.location = uri; // callback not working due to blur is not thrown on protocol dialog appear
                }else
                    this.OpenUriWithTimeout(uri, errorCallback);
            },
            
            OpenUriUsingFirefox: function (uri, errorCallback) {
                if (68 <= ITHit.DetectBrowser.FF){
                    window.location = uri; // callback not working due to blur is not thrown on protocol dialog appear
                }else
                    this.OpenUriWithTimeout(uri, errorCallback);
            },

            OpenUriUsingIE: function (uri, errorCallback) {
                if (navigator.msLaunchUri) {
                    navigator.msLaunchUri(uri, function () { }, errorCallback);
                }
                else {
                    //check if OS is Win 8 or 8.1
                    var ua = navigator.userAgent.toLowerCase();
                    var isWin8 = /windows nt 6.2/.test(ua) || /windows nt 6.3/.test(ua);

                    if (isWin8) {
                        this.OpenUriUsingIEInWindows8(uri, errorCallback);
                    } else {
                        if (ITHit.DetectBrowser.IE === 9 || ITHit.DetectBrowser.IE === 11) {
                            this.OpenUriWithHiddenFrame(uri, errorCallback);
                        } else {
                            this.OpenUriInNewWindow(uri, errorCallback);
                        }
                    }
                }
            },

            OpenUriInNewWindow: function (uri, errorCallback) {
                var myWindow = window.open('', '', 'width=0,height=0');

                myWindow.document.write("<iframe src='" + uri + "'></iframe>");
                setTimeout(function () {
                    try {
                        myWindow.setTimeout("window.close()", self.ProtocolTimeoutMs);
                    } catch (e) {
                        myWindow.close();
                        self.CallErrorCallback(errorCallback);
                    }
                }, self.ProtocolTimeoutMs);
            },

            OpenUriUsingIEInWindows8: function (uri, errorCallback) {
                window.location.href = uri;
            },

            OpenUriUsingEdgeInWindows10: function (uri, errorCallback) {
                if (navigator.msLaunchUri) {
                    if (ITHit.DetectBrowser.Edge < 15.15063) {
                        // If fail callback is provided Edge will always call fail callback, looks like an Edge bug
                        navigator.msLaunchUri(uri/*, function () { }, errorCallback*/);
                    } else {
                        navigator.msLaunchUri(uri, function () { }, errorCallback);
                    }
                }
            },

            CallEdgeExtension: function (uri, errorCallback) {
                // create unique response id
                var responseString = ITHit.WebDAV.Client.WebDavUtil.HashCode(location.href) + "_OpenUriUsingEdgeExtension_Response";
                // describe extension response listener
                var listenerCallback = function (evt) {
                    // call error callback if appropriate flag is set
                    if (evt.detail.error)
                        self.CallErrorCallback(errorCallback);
                }

                // store event listener to not add it twice
                if (window.isEventListenerAdded === undefined || !window.isEventListenerAdded[responseString]) {
                    if (window.isEventListenerAdded === undefined)
                        window.isEventListenerAdded = {};

                    // add event listener for events from extension
                    window.addEventListener(responseString, listenerCallback, false)
                    window.isEventListenerAdded[responseString] = true;
                }

                // send event with uri parameters
                var event = new CustomEvent("OpenUriUsingEdgeExtension_Request", { detail: { uri: uri } });
                window.dispatchEvent(event);
            },

            CallChromeExtension: function (uri, errorCallback) {

                // send event with uri parameters
                var event = new CustomEvent("OpenUriUsingChromeExtension_Request", { detail: { uri: uri } });
                window.dispatchEvent(event);

            },

            CallFirefoxExtension: function (uri, errorCallback) {
                // Create unique response id
                var responseString = 'OpenUriUsingFirefoxExtension_Response';

                // Describe extension response listener
                var listenerCallback = function (event) {
                    // Call error callback if appropriate flag is set
                    if (event.detail.error) {
                        self.CallErrorCallback(errorCallback);
                    }else{
                        self.OpenUriUsingFirefox(event.detail.url, errorCallback);
                    }
                };

                // Store event listener to not add it twice
                if (window.isEventListenerAdded === undefined || !window.isEventListenerAdded[responseString]) {
                    if (window.isEventListenerAdded === undefined) {
                        window.isEventListenerAdded = {};
                    }

                    // add event listener for events from extension
                    window.addEventListener(responseString, listenerCallback, false);
                    window.isEventListenerAdded[responseString] = true;
                }

                // Send event with uri parameters
                var event = new CustomEvent("OpenUriUsingFirefoxExtension_Request", {
                    detail: { uri: uri }
                });
                window.dispatchEvent(event);

            },

            OpenProtocol: function (uri, errorCallback) {
                if (ITHit.DetectBrowser.FF && !ITHit.DetectOS.IOS) {
                    this.OpenUriUsingFirefox(uri, errorCallback);
                } else if (ITHit.DetectBrowser.FF && ITHit.DetectOS.IOS) {
                    this.OpenUriWithHiddenLink(uri, errorCallback);
                } else if (ITHit.DetectBrowser.Chrome && this.IsExtensionInstalled()) {
                    if (uri.length > 2040 && ITHit.DetectOS.OS == "Windows") {
                        this.CallChromeExtension(uri, errorCallback);
                    } else {
                        window.location = uri;
                    }
                } else if (ITHit.DetectBrowser.Chrome) {
                    this.OpenUriUsingChrome(uri, errorCallback);
                } else if (ITHit.DetectBrowser.IE) {
                    if (uri.length > 2080 && ITHit.DetectOS.OS == "Windows") {
                        alert("URL is too long (" + uri.length + " characters). Internet Explorer does not support URLs longer than 2080 characters. Use Chrome, Firefox or Safari instead.");
                    } else {
                        this.OpenUriUsingIE(uri, errorCallback);
                    }
                } else if (ITHit.DetectBrowser.Safari && !ITHit.DetectOS.IOS) {
                    this.OpenUriWithHiddenFrame(uri, errorCallback);
                } else if (ITHit.DetectBrowser.Edge) {
                    if (uri.length > 2080 && ITHit.DetectOS.OS == "Windows") {
                        this.CallEdgeExtension(uri, errorCallback);
                    } else {
                        this.OpenUriUsingEdgeInWindows10(uri, errorCallback);
                    }
                }
                else {
                    this.OpenUriWithTimeout(uri, errorCallback);
                }
            },

            OpenProtocolWithCookies: function (uri, errorCallback) {
                if (ITHit.DetectBrowser.Chrome) {
                    this.CallChromeExtension(uri, errorCallback);
                } else if (ITHit.DetectBrowser.Edge && this.IsExtensionInstalled()) {
                    this.CallEdgeExtension(uri, errorCallback);
                } else if (ITHit.DetectBrowser.FF) {
                    this.CallFirefoxExtension(uri, errorCallback);
                } else {
                    this.OpenProtocol(uri, errorCallback);
                }
            }
        }
    });

})();

/**
 * @class ITHit.WebDAV.Client.Methods.CancelUpload
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.CancelUpload', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.CancelUpload.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.CancelUpload */{

		Go: function (oRequest, sHref, sLockToken, sHost) {
			return this.GoAsync(oRequest, sHref, sLockToken, sHost);
		},

		GoAsync: function (oRequest, sHref, sLockToken, sHost, fCallback) {

			// Create request.
			var oWebDavRequest = ITHit.WebDAV.Client.Methods.CancelUpload.createRequest(oRequest, sHref, sLockToken, sHost);

			var self = this;
			var fOnResponse = typeof fCallback === 'function'
				? function (oResult) {
				self._GoCallback(sHref, oResult, fCallback)
			}
				: null;

			// Get response.
			var oResponse = oWebDavRequest.GetResponse(fOnResponse);

			if (typeof fCallback !== 'function') {
				var oResult = new ITHit.WebDAV.Client.AsyncResult(oResponse, oResponse != null, null);
				return this._GoCallback(sHref, oResult, fCallback);
			} else {
				return oWebDavRequest;
			}
		},

		_GoCallback: function (sHref, oResult, fCallback) {

			var oResponse = oResult;
			var bSuccess = true;
			var oError = null;

			if (oResult instanceof ITHit.WebDAV.Client.AsyncResult) {
				oResponse = oResult.Result;
				bSuccess = oResult.IsSuccess;
				oError = oResult.Error;
			}

			// Parse response response.
			var oUnlock = null;
			if (bSuccess) {
				oUnlock = new ITHit.WebDAV.Client.Methods.CancelUpload(new ITHit.WebDAV.Client.Methods.SingleResponse(oResponse));
			}

			// Return response.
			if (typeof fCallback === 'function') {
				var oUnlockResult = new ITHit.WebDAV.Client.AsyncResult(oUnlock, bSuccess, oError);
				fCallback.call(this, oUnlockResult);
			} else {
				// Return response object.
				return oUnlock;
			}
		},

		createRequest: function (oRequest, sHref, sLockToken, sHost) {

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref, sLockToken);
			oWebDavRequest.Method('CANCELUPLOAD');

			return oWebDavRequest;
		}

	}
});




/**
 * Provides support partial uploads and resuming broken uploads.
 * @api
 * @class ITHit.WebDAV.Client.ResumableUpload
 */
ITHit.DefineClass('ITHit.WebDAV.Client.ResumableUpload', null, /** @lends ITHit.WebDAV.Client.ResumableUpload.prototype */{

	/**
	 * Current WebDAV session.
	 * @type {ITHit.WebDAV.Client.WebDavSession}
	 */
	Session: null,

	/**
	 * This item path on the server.
	 * @type {string}
	 */
	Href: null,

	/**
	 * Server host.
	 * @type {string}
	 */
	Host: null,

	/**
	 * @param {ITHit.WebDAV.Client.WebDavSession} oSession Current WebDAV session
	 * @param {string} sHref Item's path.
	 * @param {string} sHost
	 */
	constructor: function(oSession, sHref, sHost) {
		this.Session = oSession;
		this.Href = sHref;
		this.Host = sHost;
	},

	/**
	 * Amount of bytes successfully uploaded to server.
	 * @private
	 * @deprecated Use asynchronous method instead
	 * @returns {number} Number of bytes uploaded to server or -1 if server did not provide info about how much bytes uploaded.
	 * @throws ITHit.WebDAV.Client.Exceptions.NotImplementedException Is thrown if server doesn't support resumable upload.
	 * @throws ITHit.WebDAV.Client.Exceptions.LockedException This folder is locked and no or invalid lock token was specified.
	 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
	 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
	 */
	GetBytesUploaded: function() {
		var oRequest = this.Session.CreateRequest(this.__className + '.GetBytesUploaded()');
		var aUploadInfo = ITHit.WebDAV.Client.Methods.Report.Go(oRequest, this.Href, this.Host);
		var iBytes = aUploadInfo.length > 0 ? aUploadInfo[0].BytesUploaded : null;

		oRequest.MarkFinish();
		return iBytes;
	},

	/**
	 * Callback function to be called when result of bytes uploaded loaded from server.
	 * @callback ITHit.WebDAV.Client.ResumableUpload~GetBytesUploadedAsyncCallback
	 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
	 * @param {number} oResult.Result Number of bytes uploaded to server or -1 if server did not provide info about how much bytes uploaded.
	 */

	/**
	 * Get amount of bytes successfully uploaded to server.
	 * @api
	 * @param {ITHit.WebDAV.Client.ResumableUpload~GetBytesUploadedAsyncCallback} fCallback Function to call when operation is completed.
	 * @returns {ITHit.WebDAV.Client.Request} Request object.
	 */
	GetBytesUploadedAsync: function (fCallback) {
		var oRequest = this.Session.CreateRequest(this.__className + '.GetBytesUploadedAsync()');
		ITHit.WebDAV.Client.Methods.Report.GoAsync(oRequest, this.Href, this.Host, null, null, function(oAsyncResult) {
			oAsyncResult.Result = oAsyncResult.IsSuccess && oAsyncResult.Result.length > 0 ?
				oAsyncResult.Result[0].BytesUploaded :
				null;

			oRequest.MarkFinish();
			fCallback(oAsyncResult);
		});

		return oRequest;
	},

	/**
	 * Cancels upload of the file.
	 * @private
	 * @deprecated Use asynchronous method instead
	 * @param {string} mLockTokens Lock token for this file.
	 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This folder doesn't exist on the server.
	 * @throws ITHit.WebDAV.Client.Exceptions.LockedException This folder is locked and no or invalid lock token was specified.
	 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
	 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
	 */
	CancelUpload: function(mLockTokens) {
		var oRequest = this.Session.CreateRequest(this.__className + '.CancelUpload()');
		ITHit.WebDAV.Client.Methods.CancelUpload.Go(oRequest, this.Href, mLockTokens, this.Host);
		oRequest.MarkFinish();
	},

	/**
	 * Callback function to be called when folder loaded from server.
	 * @callback ITHit.WebDAV.Client.ResumableUpload~CancelUploadAsyncCallback
	 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
	 */

	/**
	 * Cancels upload of the file.
	 * @api
	 * @param {string} mLockTokens Lock token for this file.
	 * @param {ITHit.WebDAV.Client.ResumableUpload~CancelUploadAsyncCallback} fCallback Function to call when operation is completed.
	 * @returns {ITHit.WebDAV.Client.Request} Request object.
	 */
	CancelUploadAsync: function (mLockTokens, fCallback) {
		var oRequest = this.Session.CreateRequest(this.__className + '.CancelUploadAsync()');
		return ITHit.WebDAV.Client.Methods.CancelUpload.GoAsync(oRequest, this.Href, this.Host, mLockTokens, function(oAsyncResult) {

			oRequest.MarkFinish();
			fCallback(oAsyncResult);
		});
	}

});


/**
 * Information about lock set on an item.
 * @private
 * @class ITHit.WebDAV.Client.GEditInfo
 */
ITHit.DefineClass('ITHit.WebDAV.Client.GEditInfo', ITHit.WebDAV.Client.LockInfo, /** @lends ITHit.WebDAV.Client.GEditInfo.prototype */{

    __static: /** @lends ITHit.WebDAV.Client.GEditInfo */{

        /**
		 * Parses activeLocks from lockNode.
		 * @param {ITHit.XMLDoc} oElement Node containing XML Element with activeLock node.
		 * @param {string} sHref Request's URI.
		 * @returns {ITHit.WebDAV.Client.LockInfo} Information about active locks.
		 */
        ParseLockInfo: function (oElement, sHref) {

            var aSearchedGEditLock = oElement.getElementsByTagNameNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'activelock')[0];
            var lockInfo = this._super(aSearchedGEditLock, sHref);

            var oResolver = new ITHit.XPath.resolver();
            oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);
            oResolver.add('ithit', "https://www.ithit.com/geditschema/");

            var oGEditRes = ITHit.XPath.evaluate('/d:prop/ithit:gedit', oElement, oResolver);
            var oGEditID = '';
            if ((oNode = oGEditRes.iterateNext())) {
                oGEditID = oNode.firstChild().nodeValue();
            }

            var oGRevisionIDRes = ITHit.XPath.evaluate('/d:prop/ithit:grevisionid', oElement, oResolver);
            var oGRevisionID = '';
            if ((oNode = oGRevisionIDRes.iterateNext())) {
                oGRevisionID = oNode.firstChild().nodeValue();
            }

            return new ITHit.WebDAV.Client.GEditInfo(lockInfo.LockScope, lockInfo.Deep, lockInfo.Owner, lockInfo.TimeOut, lockInfo.LockToken, oGEditID, oGRevisionID);
        }
    },

    /**
     * File ID from google drive.
     * @api
     * @type {string}
    */
    GFileID: null,

    /**
     * Revision ID from google drive.
     * @api
     * @type {string}
    */
    GRevisionID: null,

    /**
	 * Initializes new instance of LockInfo.
	 * @param {ITHit.WebDAV.Client.LockScope} oLockScope Scope of the lock.
	 * @param {boolean}   bDeep Whether lock is set on item's children.
	 * @param {string} sOwner Owner's name.
	 * @param {number} iTimeOut Timeout until lock expires.
	 * @param {ITHit.WebDAV.Client.LockUriTokenPair} oLockToken Lock token.
     * @param {string} oGEditID from google drive.
	 */
    constructor: function (oLockScope, bDeep, sOwner, iTimeOut, oLockToken, oGEditID, oGRevisionID) {
        this.LockScope = oLockScope;
        this.Deep = bDeep;
        this.TimeOut = iTimeOut;
        this.Owner = sOwner;
        this.LockToken = oLockToken;
        this.GFileID = oGEditID;
        this.GRevisionID = oGRevisionID;
    }

});


/**
 * @private
 * @class ITHit.WebDAV.Client.Methods.GEdit 
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.GEdit', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.GEdit.prototype */{

    __static: /** @lends ITHit.WebDAV.Client.Methods.GEdit */{

        /**
		 *
		 * @param oRequest
		 * @param sHref
		 * @returns {ITHit.WebDAV.Client.Methods.GEdit}
		 */
        Go: function (oRequest, sHref, iTimeout) {
            return this._super.apply(this, arguments);
        },

        /**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param fCallback
		 * @returns {*}
		 */
        GoAsync: function (oRequest, sHref, iTimeout, fCallback) {
            return this._super.apply(this, arguments);
        },

        _CreateRequest: function (oRequest, sHref, iTimeout) {

            // Create request.
            var oWebDavRequest = oRequest.CreateWebDavRequest(null, sHref);
            oWebDavRequest.Method('GEDIT');

            // Add headers.
            oWebDavRequest.Headers.Add('Timeout',
				(-1 === iTimeout)
					? 'Infinite'
					: 'Second-' + parseInt(iTimeout)
			);

            return oWebDavRequest;
        },
    },

    /**
    * @type {ITHit.WebDAV.Client.GEditInfo}
    */
    GEditInfo: null,

    _Init: function () {
        // Get response data as string.
        var oXmlDoc = this.Response.GetResponseStream();

        // Create namespace resolver.
        var oResolver = new ITHit.XPath.resolver();
        oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);

        // Select property element.
        var oProp = new ITHit.WebDAV.Client.Property(ITHit.XPath.selectSingleNode('/d:prop', oXmlDoc, oResolver));

        try {
            // Parse property element.

            this.GEditInfo = new ITHit.WebDAV.Client.GEditInfo.ParseLockInfo(oProp.Value, this.Href);

            // Exception had happened.
        } catch (e) {
            throw new ITHit.WebDAV.Client.Exceptions.PropertyException(
                ITHit.Phrases.Exceptions.ParsingPropertiesException,
                this.Href,
                oProp.Name,
                null,
                ITHit.WebDAV.Client.HttpStatus.OK,
                e
            );
        }
    }


});


/**
 * @private
 * @class ITHit.WebDAV.Client.Methods.GUnlock
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.GUnlock', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.GUnlock.prototype */{

    __static: /** @lends ITHit.WebDAV.Client.Methods.GUnlock */{

        /**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param sLockToken
		 * @returns {ITHit.WebDAV.Client.Methods.GUnlock}
		 */
        Go: function (oRequest, sHref, sLockToken, sGRevisionID) {
            return this._super.apply(this, arguments);
        },

        /**
		 *
		 * @param oRequest
		 * @param sHref
		 * @param sLockToken
		 * @param fCallback
		 * @returns {*}
		 */
        GoAsync: function (oRequest, sHref, sLockToken, sGRevisionID, fCallback) {
            return this._super.apply(this, arguments);
        },

        _ProcessResponse: function (oResponse, sHref) {
            // Get appropriate response object.
            var oResp = new ITHit.WebDAV.Client.Methods.SingleResponse(oResponse);

            return this._super(oResp);
        },

        _CreateRequest: function (oRequest, sHref, sLockToken, sGRevisionID) {

            // Create request.
            var oWebDavRequest = oRequest.CreateWebDavRequest(null, sHref);
            oWebDavRequest.Method('GUNLOCK');

            // Add header.
            oWebDavRequest.Headers.Add('Lock-Token', '<' + ITHit.WebDAV.Client.DavConstants.OpaqueLockToken + sLockToken + '>');

            // Create XML DOM document object.
            var oWriter = new ITHit.XMLDoc();

            // Get namespace for XML elements.
            var sNamespaceUri = "ithit:";

            // Create root element.
            var gGUnlockInfo = oWriter.createElementNS(sNamespaceUri, 'gunlock');

            var gRevisionInfo = oWriter.createElementNS(sNamespaceUri, 'grevisionid');
            gRevisionInfo.appendChild(oWriter.createTextNode(sGRevisionID));

            gGUnlockInfo.appendChild(gRevisionInfo);
            oWriter.appendChild(gGUnlockInfo);

            // Add XML document as request body.
            oWebDavRequest.Body(oWriter);

            return oWebDavRequest;
        }

    }
});


;
(function() {

	/**
	 * Represents a file on a WebDAV server.
	 * @api
	 * @class ITHit.WebDAV.Client.File
	 * @extends ITHit.WebDAV.Client.HierarchyItem
	 */
	var self = ITHit.WebDAV.Client.Resource = ITHit.DefineClass('ITHit.WebDAV.Client.File', ITHit.WebDAV.Client.HierarchyItem, /** @lends ITHit.WebDAV.Client.File.prototype */{

		__static: /** @lends ITHit.WebDAV.Client.File */{

			GetRequestProperties: function() {
				return [
					ITHit.WebDAV.Client.DavConstants.ResourceType,
					ITHit.WebDAV.Client.DavConstants.DisplayName,
					ITHit.WebDAV.Client.DavConstants.CreationDate,
					ITHit.WebDAV.Client.DavConstants.GetLastModified,
					ITHit.WebDAV.Client.DavConstants.GetContentType,
					ITHit.WebDAV.Client.DavConstants.GetContentLength,
					ITHit.WebDAV.Client.DavConstants.SupportedLock,
					ITHit.WebDAV.Client.DavConstants.LockDiscovery,
					ITHit.WebDAV.Client.DavConstants.QuotaAvailableBytes,
					ITHit.WebDAV.Client.DavConstants.QuotaUsedBytes,
					ITHit.WebDAV.Client.DavConstants.CheckedIn,
					ITHit.WebDAV.Client.DavConstants.CheckedOut
				];
			},

			ParseHref: function(sHref, isFolder) {
				// Normalize href
				var aHrefParts  = sHref.split('?');
				aHrefParts[0]   = aHrefParts[0].replace(/\/?$/, '');
				sHref           = ITHit.WebDAV.Client.Encoder.EncodeURI(aHrefParts.join('?'));

				return this._super(sHref);
			},

			/**
			 * Load resource from server
			 * @deprecated Use asynchronous method instead
			 * @param {ITHit.WebDAV.Client.Request} oRequest Current WebDAV session.
			 * @param {string} sHref This item path on the server.
			 * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. Default is empty array.
			 * @returns {ITHit.WebDAV.Client.File} Opened folder object.
			 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException A Resource was expected or the response doesn't have required item.
			 */
			OpenItem: function(oRequest, sHref, aProperties) {
				aProperties = aProperties || [];

				var oFolder = this._super(oRequest, sHref, aProperties);

				// Throw exception if there is not a folder type.
				if (!(oFolder instanceof self)) {
					throw new ITHit.WebDAV.Client.Exceptions.WebDavException(ITHit.Phrases.ResponseFileWrongType.Paste(sHref));
				}

				return oFolder;
			},

			/**
			 * Callback function to be called when resource loaded from server.
			 * @callback ITHit.WebDAV.Client.File~OpenAsyncCallback
			 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
			 * @param {ITHit.WebDAV.Client.File} oResult.Result Loaded resource object.
			 */

			/**
			 * Load resource from server
			 * @param {ITHit.WebDAV.Client.Request} oRequest Current WebDAV session.
			 * @param {string} sHref This item path on the server.
			 * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. Default is empty array.
			 * @param {ITHit.WebDAV.Client.File~OpenAsyncCallback} fCallback Function to call when operation is completed.
			 * @returns {ITHit.WebDAV.Client.Request} Request object.
			 */
			OpenItemAsync: function(oRequest, sHref, aProperties, fCallback) {
				aProperties = aProperties || [];

				this._super(oRequest, sHref, aProperties, function(oAsyncResult) {
					// Throw exception if there is not a folder type.
					if (oAsyncResult.IsSuccess && !(oAsyncResult.Result instanceof self)) {
						oAsyncResult.Error = new ITHit.WebDAV.Client.Exceptions.WebDavException(ITHit.Phrases.ResponseFileWrongType.Paste(sHref));
						oAsyncResult.IsSuccess = false;
					}

					fCallback(oAsyncResult);
				});

				return oRequest;
			},

		    /**
             * Locks the item and upload to google drive.
             * @api
             * @param {ITHit.WebDAV.Client.Request} oRequest Current WebDAV session.  
             * @param {string} sHref This item path on the server.
             * @returns {ITHit.WebDAV.Client.GEditInfo} Instance of GEditInfo.
             */
			GEdit: function (oRequest, sHref, iTimeout) {

			    var oResult = ITHit.WebDAV.Client.Methods.GEdit.Go(
                    oRequest,
                    sHref,
                    iTimeout
                );

			    // Return response object.
			    oRequest.MarkFinish();
			    return oResult.GEditInfo;
			},

		    /**
		     * Callback function to be called when item is locked on server.
		     * @callback ITHit.WebDAV.Client.File~GEditAsyncCallback
		     * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		     * @param {ITHit.WebDAV.Client.GEditInfo} oResult.Result Instance of GEditInfo.
		     */

		    /**
             * Locks the item and upload to google drive.
             * @api
             * @param {ITHit.WebDAV.Client.Request} oRequest Current WebDAV session.  
             * @param {string} sHref This item path on the server.
             * @param {ITHit.WebDAV.Client.File~GEditAsync} fCallback Function to call when operation is completed.
             * @returns {ITHit.WebDAV.Client.Request} Request object.
             */
			GEditAsync: function (oRequest, sHref, iTimeout, fCallback) {
			    ITHit.WebDAV.Client.Methods.GEdit.GoAsync(
                    oRequest,
                    sHref,
                    iTimeout,
                    function (oAsyncResult) {
                        if (oAsyncResult.IsSuccess) {
                            oAsyncResult.Result = oAsyncResult.Result.GEditInfo;
                        }

                        oRequest.MarkFinish();
                        fCallback(oAsyncResult);
                    }
                );

			    return oRequest;
			},

             /**
		     * Removes the lock and update file.
		     * @api
		     * @param {ITHit.WebDAV.Client.Request} oRequest Current WebDAV session.  
             * @param {string} sHref This item path on the server.
		     * @param {string} [sLockToken] Identifies lock to be prolonged.
		     * @throws ITHit.WebDAV.Client.Exceptions.PreconditionFailedException The item is not locked.
		     * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException The item doesn't exist on the server.
		     * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		     */
			GUnlock: function (oRequest, sHref, sLockToken, sRevisionID) { 			 
			    // Unlock item.
			    var oResult = ITHit.WebDAV.Client.Methods.GUnlock.Go(
                    oRequest,
                    sHref,
                    sLockToken,
                    sRevisionID
                );

			    oRequest.MarkFinish();
			},


		    /**
             * Callback function to be called when item unlocked on server.
             * @callback ITHit.WebDAV.Client.File~GUnlockAsyncCallback
             * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
             */

		    /**
             * Removes the lock and update file.
             * @api
             * @param {ITHit.WebDAV.Client.Request} oRequest Current WebDAV session.  
             * @param {string} sHref This item path on the server.
             * @param {string} sLockToken Identifies lock to be prolonged.
             * @param {string} sRevisionID Revision ID of google file.
             * @param {ITHit.WebDAV.Client.File~GUnlockAsyncCallback} fCallback Function to call when operation is completed.
             * @returns {ITHit.WebDAV.Client.Request} Request object.
             */
			GUnlockAsync: function (oRequest, sHref, sLockToken, sRevisionID, fCallback) {
			    ITHit.WebDAV.Client.Methods.GUnlock.GoAsync(
                    oRequest,
                    sHref,
                    sLockToken,
                    sRevisionID,
                    function (oAsyncResult) {
                        oRequest.MarkFinish();
                        fCallback(oAsyncResult);
                    }
                );

			    return oRequest;
			}

		},

		/**
		 * Length of the file.
         * @api
		 * @type {number}
		 */
		ContentLength: null,

		/**
		 * Content type of the file.
         * @api
		 * @type {string}
		 */
		ContentType: null,

		/**
		 * ResumableUpload instance to manage partially failed uploads.
		 * @api
		 * @type {ITHit.WebDAV.Client.ResumableUpload}
		 */
		ResumableUpload: null,

		/**
		 * Create new instance of File class which represents a file on a WebDAV server.
		 * @param {ITHit.WebDAV.Client.WebDavSession} oSession Current WebDAV session.
		 * @param {string} sHref This item path on the server.
		 * @param {object} oGetLastModified Most recent modification date.
		 * @param {string} sDisplayName User friendly item name.
		 * @param {object} oCreationDate The date item was created.
		 * @param {string} sContentType Content type.
		 * @param {number} iContentLength Content length.
		 * @param aSupportedLocks
		 * @param aActiveLocks
		 * @param sHost
		 * @param iAvailableBytes
		 * @param iUsedBytes
		 * @param aCheckedIn
		 * @param aCheckedOut
		 * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties
		 */
		constructor: function(oSession, sHref, oGetLastModified, sDisplayName, oCreationDate, sContentType, iContentLength, aSupportedLocks, aActiveLocks, sHost, iAvailableBytes, iUsedBytes, aCheckedIn, aCheckedOut, aProperties) {

			// Inheritance definition.
			this._super(oSession, sHref, oGetLastModified, sDisplayName, oCreationDate, ITHit.WebDAV.Client.ResourceType.File, aSupportedLocks, aActiveLocks, sHost, iAvailableBytes, iUsedBytes, aCheckedIn, aCheckedOut, aProperties);

			// Declare class properties.
			this.ContentLength = iContentLength;
			this.ContentType   = sContentType;

			this.ResumableUpload = new ITHit.WebDAV.Client.ResumableUpload(this.Session, this.Href);
		},

		/**
		 * Reads file content.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {number} [iBytesFrom] Start position to retrieve lBytesCount number of bytes from.
		 * @param {number} [iBytesCount] Number of bytes to retrieve.
		 * @returns {string} Requested file content.
		 */
		ReadContent: function(iBytesFrom, iBytesCount) {
			iBytesFrom = iBytesFrom || null;
			iBytesCount = iBytesCount || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.ReadContent()');

			var iBytesTo = iBytesFrom && iBytesCount ? iBytesFrom + iBytesCount - 1 : 0;

			// Create response.
			var oResult = ITHit.WebDAV.Client.Methods.Get.Go(
				oRequest,
				this.Href,
				iBytesFrom,
				iBytesTo,
				this.Host
			);

			// Return requested content.
			oRequest.MarkFinish();
			return oResult.GetContent();
		},

		/**
		 * Callback function to be called when file content loaded from server.
		 * @callback ITHit.WebDAV.Client.File~ReadContentAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 * @param {string} oResult.Result Requested file content.
		 */

		/**
		 * Reads file content. To download only a part of a file you can specify 2 parameters in ReadContent call.
		 * First parameter is the starting byte (zero-based) at witch to start content download, the second – amount
		 * of bytes to be downloaded. The library will add Range header to the request in this case.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.CreateFile.ReadContent
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.CreateFile.ReadContentRange
		 * @param {number} iBytesFrom Start position to retrieve lBytesCount number of bytes from.
		 * @param {number} iBytesCount Number of bytes to retrieve.
		 * @param {ITHit.WebDAV.Client.File~ReadContentAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		ReadContentAsync: function(iBytesFrom, iBytesCount, fCallback) {
			iBytesFrom = iBytesFrom || null;
			iBytesCount = iBytesCount || null;

			var oRequest = this.Session.CreateRequest(this.__className + '.ReadContentAsync()');

			var iBytesTo = iBytesFrom && iBytesCount ? iBytesFrom + iBytesCount - 1 : null;

			// Create response.
			ITHit.WebDAV.Client.Methods.Get.GoAsync(
				oRequest,
				this.Href,
				iBytesFrom,
				iBytesTo,
				this.Host,
				function(oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						oAsyncResult.Result = oAsyncResult.Result.GetContent();
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		/**
		 * Writes file content.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {string} sContent File content.
		 * @param {string} [sLockToken] Lock token.
		 * @param {string} [sMimeType] File mime-type.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Content is not writtened to file.
		 */
		WriteContent: function(sContent, sLockToken, sMimeType) {
			sLockToken = sLockToken || null;
			sMimeType = sMimeType || '';

			var oRequest = this.Session.CreateRequest(this.__className + '.WriteContent()');

			// Create response.
			var oResult = ITHit.WebDAV.Client.Methods.Put.Go(
				oRequest,
				this.Href,
				sMimeType,
				sContent,
				sLockToken,
				this.Host
			);

			var oError = this._GetErrorFromWriteContentResponse(oResult.Response, this.Href);
			if (oError) {
				oRequest.MarkFinish();
				throw oError;
			}

			oRequest.MarkFinish();
		},

		/**
		 * Callback function to be called when content saved in file on server.
		 * @callback ITHit.WebDAV.Client.File~WriteContentAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Writes file content.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.CreateFile.OnlyWriteContent
		 * @param {string} sContent File content.
		 * @param {string} sLockToken Lock token.
		 * @param {string} sMimeType File mime-type.
		 * @param {ITHit.WebDAV.Client.File~WriteContentAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		WriteContentAsync: function(sContent, sLockToken, sMimeType, fCallback) {
			sLockToken = sLockToken || null;
			sMimeType = sMimeType || '';

			var oRequest = this.Session.CreateRequest(this.__className + '.WriteContentAsync()');

			// Create response.
			var that = this;
			ITHit.WebDAV.Client.Methods.Put.GoAsync(
				oRequest,
				this.Href,
				sMimeType,
				sContent,
				sLockToken,
				this.Host,
				function (oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						oAsyncResult.Error = that._GetErrorFromWriteContentResponse(oAsyncResult.Result.Response, that.Href);
						if (oAsyncResult.Error !== null) {
							oAsyncResult.IsSuccess = false;
							oAsyncResult.Result = null;
						}
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		/**
		 * Opens document for editting.
		 * @private
		 * @param {string} [sJavaAppletUrl] Url to Java Applet to use for opening the documents in case web browser plugin is not found.
		 */
		EditDocument: function (sJavaAppletUrl) {
			ITHit.WebDAV.Client.DocManager.EditDocument(this.Href, sJavaAppletUrl);
		},

		/**
		 * Retrieves item versions.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @returns {ITHit.WebDAV.Client.Version[]} List of Versions.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This item doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
		 */
		GetVersions: function() {

			var oRequest = this.Session.CreateRequest(this.__className + '.GetVersions()');

			var oResult = ITHit.WebDAV.Client.Methods.Report.Go(
				oRequest,
				this.Href,
				this.Host,
				ITHit.WebDAV.Client.Methods.Report.ReportType.VersionsTree,
				ITHit.WebDAV.Client.Version.GetRequestProperties()
			);

			var aVersions = ITHit.WebDAV.Client.Version.GetVersionsFromMultiResponse(oResult.Response.Responses, this);

			oRequest.MarkFinish();
			return aVersions;
		},

		/**
		 * Callback function to be called when versions list loaded from server.
		 * @callback ITHit.WebDAV.Client.File~GetVersionsAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 * @param {ITHit.WebDAV.Client.Version[]} oResult.Result List of Versions.
		 */

		/**
		 * Retrieves item versions.
		 * @examplecode ITHit.WebDAV.Client.Tests.Versions.GetVersions.GetVersions
		 * @api
		 * @param {ITHit.WebDAV.Client.File~GetVersionsAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		GetVersionsAsync: function(fCallback) {

			var oRequest = this.Session.CreateRequest(this.__className + '.GetVersionsAsync()');

			var that = this;
			ITHit.WebDAV.Client.Methods.Report.GoAsync(
				oRequest,
				this.Href,
				this.Host,
				ITHit.WebDAV.Client.Methods.Report.ReportType.VersionsTree,
				ITHit.WebDAV.Client.Version.GetRequestProperties(),
				function(oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						oAsyncResult.Result = ITHit.WebDAV.Client.Version.GetVersionsFromMultiResponse(oAsyncResult.Result.Response.Responses, that);
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				}
			);

			return oRequest;
		},

		/**
		 * Update to version.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {string|ITHit.WebDAV.Client.Version} mVersion Href to file with version attribute or {@link ITHit.WebDAV.Client.Version} instance.
		 * @returns {boolean}
		 */
		UpdateToVersion: function(mVersion) {
			var sToHrefUpdate = mVersion instanceof ITHit.WebDAV.Client.Version ?
				mVersion.Href :
				mVersion;

			var oRequest = this.Session.CreateRequest(this.__className + '.UpdateToVersion()');

			// Make request.
			var oResult = ITHit.WebDAV.Client.Methods.UpdateToVersion.Go(oRequest, this.Href, this.Host, sToHrefUpdate);

			// Get response.
			var oResponse = oResult.Response;

			// Check status
			var bIsSuccess = oResponse.Responses[0].Status.IsSuccess();

			oRequest.MarkFinish();
			return bIsSuccess;
		},

		/**
		 * Callback function to be called when version is updated on server.
		 * @callback ITHit.WebDAV.Client.File~UpdateToVersionAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Update to version.
		 * @examplecode ITHit.WebDAV.Client.Tests.Versions.ManageVersions.UpdateToVersion
		 * @api
		 * @param {string|ITHit.WebDAV.Client.Version} mVersion Href to file with version attribute or {@link ITHit.WebDAV.Client.Version} instance.
		 * @param {ITHit.WebDAV.Client.File~UpdateToVersionAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		UpdateToVersionAsync: function(mVersion, fCallback) {
			var sToHrefUpdate = mVersion instanceof ITHit.WebDAV.Client.Version ?
				mVersion.Href :
				mVersion;

			var oRequest = this.Session.CreateRequest(this.__className + '.UpdateToVersionAsync()');

			// Make request.
			ITHit.WebDAV.Client.Methods.UpdateToVersion.GoAsync(oRequest, this.Href, this.Host, sToHrefUpdate, function(oAsyncResult) {
				oAsyncResult.Result = oAsyncResult.IsSuccess && oAsyncResult.Result.Response.Responses[0].Status.IsSuccess();

				oRequest.MarkFinish();
				fCallback(oAsyncResult);
			});

			return oRequest;
		},

		/**
		 * Callback function to be called when versioning is enabled or disabled.
		 * @callback ITHit.WebDAV.Client.File~PutUnderVersionControlAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Enables / disables version control for this file.
		 * @private
		 * @deprecated Use asynchronous method instead
		 * @param {boolean} bEnable True to enable version-control, false - to disable.
		 * @param {string} [mLockToken] Lock token for this item.
		 * @throws ITHit.WebDAV.Client.Exceptions.LockedException This item is locked and invalid lock token was provided.
		 * @throws ITHit.WebDAV.Client.Exceptions.UnauthorizedException Request is not authorized.
		 * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This file doesn't exist on the server.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
		 * @throws ITHit.WebDAV.Client.Exceptions.WebDavException In case of any unexpected error.
		 */
		PutUnderVersionControl: function(bEnable, mLockToken) {
			mLockToken = mLockToken || null;

			var oRequest = null;
			var oResult = null;

			if (bEnable) {
				oRequest = this.Session.CreateRequest(this.__className + '.PutUnderVersionControl()');

				oResult = ITHit.WebDAV.Client.Methods.VersionControl.Go(oRequest, this.Href, mLockToken, this.Host);

				var oError = this._GetErrorFromPutUnderVersionControlResponse(oResult.Response);
				if (oError) {
					oRequest.MarkFinish();
					throw oError;
				}

				oRequest.MarkFinish();
			} else {
				oRequest = this.Session.CreateRequest(this.__className + '.PutUnderVersionControl()', 2);

				oResult = ITHit.WebDAV.Client.Methods.Propfind.Go(
					oRequest,
					this.Href,
					ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
					[ITHit.WebDAV.Client.DavConstants.VersionHistory],
					ITHit.WebDAV.Client.Depth.Zero,
					this.Host
				);

				var oProperty = self.GetPropertyValuesFromMultiResponse(oResult.Response, this.Href);

				var aUrls = ITHit.WebDAV.Client.Version.ParseSetOfHrefs(oProperty);
				if (aUrls.length !== 1) {
					throw new ITHit.WebDAV.Client.Exceptions.PropertyException(ITHit.Phrases.ExceptionWhileParsingProperties, this.Href,
						ITHit.WebDAV.Client.DavConstants.VersionHistory, null, ITHit.WebDAV.Client.HttpStatus.None, null);
				}

				oResult = ITHit.WebDAV.Client.Methods.Delete.Go(oRequest, aUrls[0], mLockToken, this.Host);

				var oError = this._GetErrorFromDeleteResponse(oResult.Response);
				if (oError) {
					oRequest.MarkFinish();
					throw oError;
				}

				oRequest.MarkFinish();
			}
		},

		/**
		 * Enables / disables version control for this file.
		 * @api
		 * @examplecode ITHit.WebDAV.Client.Tests.Versions.PutUnderVersion.EnableVersion
		 * @param {boolean} bEnable True to enable version-control, false - to disable.
		 * @param {string} mLockToken Lock token for this item.
		 * @param {ITHit.WebDAV.Client.File~PutUnderVersionControlAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		PutUnderVersionControlAsync: function(bEnable, mLockToken, fCallback) {
			mLockToken = mLockToken || null;

			var that = this;
			var oRequest = null;

			if (bEnable) {
				oRequest = this.Session.CreateRequest(this.__className + '.PutUnderVersionControlAsync()');

				ITHit.WebDAV.Client.Methods.VersionControl.GoAsync(oRequest, this.Href, mLockToken, this.Host, function(oAsyncResult) {
					if (oAsyncResult.IsSuccess) {
						oAsyncResult.Error = that._GetErrorFromPutUnderVersionControlResponse(oAsyncResult.Result.Response);
						if (oAsyncResult.Error !== null) {
							oAsyncResult.IsSuccess = false;
							oAsyncResult.Result = null;
						}
					}

					oRequest.MarkFinish();
					fCallback(oAsyncResult);
				});

				return oRequest;
			} else {
				oRequest = this.Session.CreateRequest(this.__className + '.PutUnderVersionControlAsync()', 2);

				ITHit.WebDAV.Client.Methods.Propfind.GoAsync(
					oRequest,
					this.Href,
					ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
					[ITHit.WebDAV.Client.DavConstants.VersionHistory],
					ITHit.WebDAV.Client.Depth.Zero,
					this.Host,
					function(oAsyncResult) {
						if (oAsyncResult.IsSuccess) {
							try {
								oAsyncResult.Result = self.GetPropertyValuesFromMultiResponse(oAsyncResult.Result.Response, that.Href);
							} catch(oError) {
								oAsyncResult.Error = oError;
								oAsyncResult.IsSuccess = false;
							}
						}

						if (oAsyncResult.IsSuccess) {
							var aUrls = ITHit.WebDAV.Client.Version.ParseSetOfHrefs(oAsyncResult.Result);
							if (aUrls.length !== 1) {
								throw new ITHit.WebDAV.Client.Exceptions.PropertyException(ITHit.Phrases.ExceptionWhileParsingProperties, that.Href,
									ITHit.WebDAV.Client.DavConstants.VersionHistory, null, ITHit.WebDAV.Client.HttpStatus.None, null);
							}

							ITHit.WebDAV.Client.Methods.Delete.GoAsync(oRequest, aUrls[0], mLockToken, that.Host, function(oAsyncResult) {
								if (oAsyncResult.IsSuccess) {
									oAsyncResult.Error = that._GetErrorFromDeleteResponse(oAsyncResult.Result.Response);
									if (oAsyncResult.Error !== null) {
										oAsyncResult.IsSuccess = false;
										oAsyncResult.Result = null;
									}
								}

								oRequest.MarkFinish();
								fCallback(oAsyncResult);
							});

						} else if (oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.PropertyNotFoundException) {
							oAsyncResult.IsSuccess = true;
							oAsyncResult.Error = null;
							oAsyncResult.Result = null;

							oRequest.MarkFinish();
							fCallback(oAsyncResult);
						} else {

							oRequest.MarkFinish();
							fCallback(oAsyncResult);
						}
					}
				);
			}
		},

		_GetErrorFromPutUnderVersionControlResponse: function(oResponse) {
			if (!oResponse.Status.IsSuccess()) {
				return new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(ITHit.Phrases.PutUnderVersionControlFailed, this.Href, null, oResponse.Status, null);
			}

			return null;
		},

		_GetErrorFromWriteContentResponse: function(oResponse, sHref) {

			// Whether content is not saved.
			if ( !oResponse.Status.Equals(ITHit.WebDAV.Client.HttpStatus.OK) && !oResponse.Status.Equals(ITHit.WebDAV.Client.HttpStatus.NoContent) ) {
				return new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(ITHit.Phrases.Exceptions.FailedToWriteContentToFile, sHref, null, oResponse.Status, null);
			}

			return null;
		}

	});

})();
(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.CancellableResult',
        ITHit.WebDAV.Client.AsyncResult,
        /** @lends ITHit.WebDAV.Client.CancellableResult.prototype */ {

            /**
             * Flag of either async request result was aborted.
             * @public
             * @type {boolean}
             */
            IsAborted: false,


            /**
             * @alias ITHit.WebDAV.Client.CancellableResult
             * @constructs
             * @extends ITHit.WebDAV.Client.AsyncResult
             * @param {*} oResult
             * @param {boolean} bSuccess
             * @param {ITHit.WebDAV.Client.Exceptions.WebDavException|Error|null} oError
             * @param {boolean} [bIsAborted=false]
             */
            constructor: function(oResult, bSuccess, oError, bIsAborted) {
                bIsAborted = bIsAborted || false;
                this._super(oResult, bSuccess, oError);
                this.IsAborted = bIsAborted;
            }
        },
        /** @lends ITHit.WebDAV.Client.CancellableResult */
        {
            /**
             * Creates aborted result.
             * @param {ITHit.WebDAV.Client.Exceptions.WebDavException|Error|null} oError
             * @return {ITHit.WebDAV.Client.CancellableResult}
             */
            CreateAbortedResult: function(oError) {
                return new ITHit.WebDAV.Client.CancellableResult(null, false, oError, true);
            },

            /**
             * Creates successful result.
             * @param {Object} oResult
             * @return {ITHit.WebDAV.Client.CancellableResult}
             */
            CreateSuccessfulResult: function(oResult) {
                return new ITHit.WebDAV.Client.CancellableResult(oResult, true, null);
            },

            /**
             * Creates failed result.
             * @param {ITHit.WebDAV.Client.Exceptions.WebDavException|Error|null} oError
             * @return {ITHit.WebDAV.Client.CancellableResult}
             */
            CreateFailedResult: function(oError) {
                return new ITHit.WebDAV.Client.CancellableResult(null, false, oError);
            },

            /**
             * Creates failed result.
             * @param {ITHit.WebDAV.Client.AsyncResult} oAsyncResult
             * @return {ITHit.WebDAV.Client.CancellableResult}
             */
            CreateFromAsyncResultResult: function(oAsyncResult) {
                return new ITHit.WebDAV.Client.CancellableResult(oAsyncResult.Result, oAsyncResult.IsSuccess, oAsyncResult.Error);
            }

        });
})();


/**
 * @class ITHit.WebDAV.Client.Methods.Mkcol
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Mkcol', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Mkcol.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Mkcol */{

		Go: function (oRequest, sHref, sLockToken, sHost) {
			// Create request.
			var oWebDavRequest = this.createRequest(oRequest, sHref, sLockToken, sHost);

			var oResponse = oWebDavRequest.GetResponse();
			var oSingleResponse = new ITHit.WebDAV.Client.Methods.SingleResponse(oResponse);
			return new ITHit.WebDAV.Client.Methods.Mkcol(oSingleResponse);
		},

		GoAsync: function (oRequest, sHref, sLockToken, sHost, fCallback) {
			// Create request.
			var oWebDavRequest = this.createRequest(oRequest, sHref, sLockToken, sHost);

			oWebDavRequest.GetResponse(function (oAsyncResult) {
				if (!oAsyncResult.IsSuccess) {
					fCallback(oAsyncResult);
					return;
				}

				var oSingleResponse = new ITHit.WebDAV.Client.Methods.SingleResponse(oAsyncResult.Result);
				var oMkcol = new ITHit.WebDAV.Client.Methods.Mkcol(oSingleResponse);
				fCallback(ITHit.WebDAV.Client.CancellableResult.CreateSuccessfulResult(oMkcol));
			});

			return oWebDavRequest;
		},

		createRequest: function (oRequest, sHref, sLockToken, sHost) {

			// Creare request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref, sLockToken);
			oWebDavRequest.Method('MKCOL');

			return oWebDavRequest;
		}

	}
});


;
(function () {

	/**
	 * @class ITHit.WebDAV.Client.Methods.Head
	 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
	 */
	var self = ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Head', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Head.prototype */{

		__static: /** @lends ITHit.WebDAV.Client.Methods.Head */{

			Go: function (oRequest, sHref, sHost) {
				try {
					return this._super.apply(this, arguments);
				} catch (oException) {

					// Check whether exception is an instance of NotFoundException class.
					if (oException instanceof ITHit.WebDAV.Client.Exceptions.NotFoundException) {
						var oResult = new self(null, sHref);
						oResult.IsOK = false;
						return oResult;
					}

					// Rethrow exception for all other cases.
					throw oException;
				}
			},

			GoAsync: function (oRequest, sHref, sHost, fCallback) {
				return this._super(oRequest, sHref, sHost, function (oAsyncResult) {
					if (oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.NotFoundException) {
						oAsyncResult.Result = new self(null, sHref);
						oAsyncResult.Result.IsOK = false;
						oAsyncResult.IsSuccess = true;
						oAsyncResult.Error = null;
					}

					fCallback(oAsyncResult);
				});
			},

			_ProcessResponse: function (oResponse, sHref) {
				var oResult = this._super(oResponse, sHref);
				oResult.IsOK = oResponse.Status.Equals(ITHit.WebDAV.Client.HttpStatus.OK);
				return oResult;
			},

			_CreateRequest: function (oRequest, sHref, sHost) {
				// Create request.
				var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref);
				oWebDavRequest.Method('HEAD');

				return oWebDavRequest;
			}

		},

		/**
		 * @type {boolean}
		 */
		IsOK: null
	});

})();


ITHit.DefineClass('ITHit.WebDAV.Client.SearchQuery', null, /** @lends ITHit.WebDAV.Client.SearchQuery.prototype */{

	/**
	 * Search phrase.
	 * @api
	 * @type {string}
	 */
	Phrase: null,

	/**
	 * <p>Properties to be returned from server with each item returned in search results.</p> 
     * <p>This property can be used to request any additional data required in search results, such as snippet of 
     * text around the search phrase, document title, author name, etc.</p>
	 * @api
	 * @type {ITHit.WebDAV.Client.PropertyName[]}
	 */
	SelectProperties: null,

	/**
	 * Enables or disables search by properties specified in <code>LikeProperties</code> list. Default is <code>true</code>.
	 * @api
	 * @type {boolean}
	 */
	EnableLike: null,

	/**
	 * List of properties to be used in like conditions. The search phrase will be searched in the properties specilied in this list.
	 * @api
	 * @type {ITHit.WebDAV.Client.PropertyName[]}
	 */
	LikeProperties: null,

	/**
	 * Enables or disables search inside file content. Default is <code>true</code>.
	 * @api
	 * @type {boolean}
	 */
	EnableContains: null,

    /**
     * @classdesc Represents a search request.
	 * @constructs
	 * @api
	 * @param {string} sSearchPhrase Search phrase.
	 */
	constructor: function(sSearchPhrase) {
		this.Phrase = sSearchPhrase;
		this.SelectProperties = [];
		this.EnableLike = true;
		this.LikeProperties = [
			ITHit.WebDAV.Client.DavConstants.DisplayName
		];
		this.EnableContains = true;
	}

});


/**
 * @class ITHit.WebDAV.Client.Methods.Search
 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Search', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.Search.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Search */{

		Go: function (oRequest, sHref, sHost, oSearchQuery) {
			// Create request.
			var oWebDavRequest = this._createRequest(oRequest, sHref, sHost, oSearchQuery);
			var oResponse = oWebDavRequest.GetResponse();

			return this._ProcessResponse(oResponse)
		},

		GoAsync: function (oRequest, sHref, sHost, oSearchQuery, fCallback, offset, nResults) {
			// Create request.
		    var oWebDavRequest = this._createRequest(oRequest, sHref, sHost, oSearchQuery, offset, nResults);

			var that = this;
			oWebDavRequest.GetResponse(function (oAsyncResult) {
				if (!oAsyncResult.IsSuccess) {
					fCallback(new ITHit.WebDAV.Client.AsyncResult(null, false, oAsyncResult.Error));
					return;
				}

				var oResult = that._ProcessResponse(oAsyncResult.Result, sHref);
				fCallback(new ITHit.WebDAV.Client.AsyncResult(oResult, true, null));
			});

			return oWebDavRequest;
		},

		_ProcessResponse: function (oResponse, sUri) {
			// Receive data.
			var oResponseData = oResponse.GetResponseStream();

			var oMultiResponse = new ITHit.WebDAV.Client.Methods.MultiResponse(oResponseData, sUri);

			// Return result object.
			return new ITHit.WebDAV.Client.Methods.Search(oMultiResponse);
		},

		_createRequest: function (oRequest, sHref, sHost, oSearchQuery, offset, nResults) {

			/*
			 Search example request:
			 <d:searchrequest xmlns:d="DAV:" >
			 <d:basicsearch>
			 <d:select>
			 <d:prop><d:allprop/></d:prop>
			 </d:select>
			 <d:where>
			 <d:or>
			 <d:like>
			 <d:prop><d:displayname/></d:prop>
			 <d:literal>search phrase</d:literal>
			 </d:like>
			 <d:contains>search phrase</d:contains>
			 </d:or>
			 </d:where>
			 </d:basicsearch>
			 </d:searchrequest>
			 */

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref);
			oWebDavRequest.Method('SEARCH');

			// Create XML document.
			var oWriter = new ITHit.XMLDoc();
			var nsDavConstants = ITHit.WebDAV.Client.DavConstants;
			var sNamespaceUri = nsDavConstants.NamespaceUri;

			// Select block
			var eSelectProp = oWriter.createElementNS(sNamespaceUri, 'prop');
			if (oSearchQuery.SelectProperties && oSearchQuery.SelectProperties.length > 0) {
				// Selected properties.
				for (var i = 0; i < oSearchQuery.SelectProperties.length; i++) {
					eSelectProp.appendChild(oWriter.createElementNS(oSearchQuery.SelectProperties[i].NamespaceUri, oSearchQuery.SelectProperties[i].Name));
				}
			} else {
				// All properties.
				eSelectProp.appendChild(sNamespaceUri, 'allprop');
			}
			var eSelect = oWriter.createElementNS(sNamespaceUri, 'select');
			eSelect.appendChild(eSelectProp);

			// Where like
			var eLike = null;
			if (oSearchQuery.EnableLike) {
				var eWhereProp = oWriter.createElementNS(sNamespaceUri, 'prop');
				if (oSearchQuery.LikeProperties && oSearchQuery.LikeProperties.length > 0) {
					for (var i = 0; i < oSearchQuery.LikeProperties.length; i++) {
						eWhereProp.appendChild(oWriter.createElementNS(oSearchQuery.LikeProperties[i].NamespaceUri, oSearchQuery.LikeProperties[i].Name));
					}
				}
				var eLiteral = oWriter.createElementNS(sNamespaceUri, 'literal');
				eLiteral.appendChild(
					oWriter.createTextNode(oSearchQuery.Phrase)
				);
				eLike = oWriter.createElementNS(sNamespaceUri, 'like');
				eLike.appendChild(eWhereProp);
				eLike.appendChild(eLiteral);
			}

			// Where contains
			var eContains = null;
			if (oSearchQuery.EnableContains) {
				eContains = oWriter.createElementNS(sNamespaceUri, 'contains');
				eContains.appendChild(
					oWriter.createTextNode(oSearchQuery.Phrase)
				);
			}

			// Where block
			var eWhere = oWriter.createElementNS(sNamespaceUri, 'where');
			if (eLike && eContains) {
				var eOr = oWriter.createElementNS(sNamespaceUri, 'or');
				eOr.appendChild(eLike);
				eOr.appendChild(eContains);
				eWhere.appendChild(eOr);
			} else if (eLike) {
				eWhere.appendChild(eLike);
			} else if (eContains) {
				eWhere.appendChild(eContains);
			}

			var basicSearch = oWriter.createElementNS(sNamespaceUri, 'basicsearch');
			basicSearch.appendChild(eSelect);
			basicSearch.appendChild(eWhere);

			// Root block
			var eSearchRequest = oWriter.createElementNS(sNamespaceUri, 'searchrequest');
			eSearchRequest.appendChild(basicSearch);     

		    // add limit child nodes
			if (offset !== undefined && offset != null && nResults !== undefined && nResults != null) {
			    var limit = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'limit');
			    var eOffset = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'offset');
			    var eNResults = oWriter.createElementNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'nresults');

			    eOffset.appendChild(oWriter.createTextNode(offset));
			    eNResults.appendChild(oWriter.createTextNode(nResults));
			    limit.appendChild(eNResults);
			    limit.appendChild(eOffset);
			    eSearchRequest.appendChild(limit);
			}

			oWriter.appendChild(eSearchRequest);       		

			// Assign created document as body for request.
			oWebDavRequest.Body(oWriter);

			// Return request object.
			return oWebDavRequest;
		}
	}
});

/**
 * Array of file and folder items that correspond to the offset, number of items and sorting conditions requested from server.
 * Also contains a total number of items in this folder or in search results.
 * @api
 * @class ITHit.WebDAV.Client.PageResults
 */
ITHit.DefineClass('ITHit.WebDAV.Client.PageResults', null, /** @lends ITHit.WebDAV.Client.PageResults.prototype */{

    /**
	 * Total number of items in the folder or in search results.
	 * @api
	 * @type {number}
	 */
    TotalItems: null,

    /**
	 * Items that correspond to the requested page and sorting.
	 * @api
	 * @type {ITHit.WebDAV.Client.HierarchyItem[]}
	 */
    Page: null,

	/**
	 *
	 * @param {ITHit.WebDAV.Client.HierarchyItem[]} items
     * @param {number} totalItems
	 */
    constructor: function (items, totalItems) {
        this.Page = items;
        this.TotalItems = totalItems;
    }

});


;
(function() {

    /**
     * Represents a folder in a WebDAV repository.
     * @api
     * @class ITHit.WebDAV.Client.Folder
     * @extends ITHit.WebDAV.Client.HierarchyItem
     */
    var self = ITHit.DefineClass('ITHit.WebDAV.Client.Folder', ITHit.WebDAV.Client.HierarchyItem, /** @lends ITHit.WebDAV.Client.Folder.prototype */{

        __static: /** @lends ITHit.WebDAV.Client.Folder */{

            GetRequestProperties: function() {
                return [
                    ITHit.WebDAV.Client.DavConstants.ResourceType,
                    ITHit.WebDAV.Client.DavConstants.DisplayName,
                    ITHit.WebDAV.Client.DavConstants.CreationDate,
                    ITHit.WebDAV.Client.DavConstants.GetLastModified,
                    ITHit.WebDAV.Client.DavConstants.SupportedLock,
                    ITHit.WebDAV.Client.DavConstants.LockDiscovery,
                    ITHit.WebDAV.Client.DavConstants.QuotaAvailableBytes,
                    ITHit.WebDAV.Client.DavConstants.QuotaUsedBytes,
                    ITHit.WebDAV.Client.DavConstants.CheckedIn,
                    ITHit.WebDAV.Client.DavConstants.CheckedOut
                ];
            },

            ParseHref: function(sHref) {
                // Normalize href
                var aHrefParts = sHref.split('?');
                aHrefParts[0] = aHrefParts[0].replace(/\/?$/, '/');
                sHref = ITHit.WebDAV.Client.Encoder.EncodeURI(aHrefParts.join('?'));

                return this._super(sHref);
            },

            /**
             * Open folder.
             * @private
             * @deprecated Use asynchronous method instead
             * @param {ITHit.WebDAV.Client.Request} oRequest Current WebDAV session.
             * @param {string} sHref This item path on the server.
			 * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. Default is empty array.
             * @returns {ITHit.WebDAV.Client.Folder} Loaded folder object.
             * @throws ITHit.WebDAV.Client.Exceptions.WebDavException A Folder was expected or the response doesn't have required item.
             */
            OpenItem: function(oRequest, sHref, aProperties) {
				aProperties = aProperties || [];

                var oFolder = this._super(oRequest, sHref, aProperties);

                // Throw exception if there is not a folder type.
                if (!(oFolder instanceof self)) {
                    throw new ITHit.WebDAV.Client.Exceptions.WebDavException(ITHit.Phrases.ResponseFolderWrongType.Paste(sHref));
                }

                return oFolder;
            },

            /**
             * Callback function to be called when folder loaded from server.
             * @callback ITHit.WebDAV.Client.Folder~OpenItemAsyncCallback
             * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
             * @param {ITHit.WebDAV.Client.Folder} oResult.Result Loaded folder object.
             */

            /**
             * Open folder.
             * @param {ITHit.WebDAV.Client.Request} oRequest Current WebDAV session.
             * @param {string} sHref This item path on the server.
			 * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. Default is empty array.
             * @param {ITHit.WebDAV.Client.Folder~OpenItemAsyncCallback} fCallback Function to call when operation is completed.
             * @returns {ITHit.WebDAV.Client.Request} Request object.
             */
            OpenItemAsync: function(oRequest, sHref, aProperties, fCallback) {
				aProperties = aProperties || [];

                return this._super(oRequest, sHref, aProperties, function(oAsyncResult) {
                    // Throw exception if there is not a resource type.
                    if (oAsyncResult.IsSuccess && !(oAsyncResult.Result instanceof self)) {
                        oAsyncResult.Error = new ITHit.WebDAV.Client.Exceptions.WebDavException(ITHit.Phrases.ResponseFolderWrongType.Paste(sHref));
                        oAsyncResult.IsSuccess = false;
                    }

                    fCallback(oAsyncResult);
                });
            }

        },

        /**
         * Create new instance of Folder class which represents a folder in a WebDAV repository.
         * @param {ITHit.WebDAV.Client.WebDavSession} oSession Current WebDAV session.
         * @param {string} sHref This item path on the server.
         * @param {object} oGetLastModified Most recent modification date.
         * @param {string} sDisplayName User friendly item name.
         * @param {object} oCreationDate The date item was created.
         * @param {Array} aSupportedLocks
         * @param {Array} aActiveLocks
         * @param {string} sHost
         * @param {number} iAvailableBytes
         * @param {number} iUsedBytes
         * @param {Array} aCheckedIn
         * @param {Array} aCheckedOut
         * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties
         */
        constructor: function(oSession, sHref, oGetLastModified, sDisplayName, oCreationDate, aSupportedLocks, aActiveLocks, sHost, iAvailableBytes, iUsedBytes, aCheckedIn, aCheckedOut, aProperties) {
            sHref = sHref.replace(/\/?$/, '/');

            this._super(oSession, sHref, oGetLastModified, sDisplayName, oCreationDate, ITHit.WebDAV.Client.ResourceType.Folder, aSupportedLocks, aActiveLocks, sHost, iAvailableBytes, iUsedBytes, aCheckedIn, aCheckedOut, aProperties);

            // Normalize folder shortcuts, force set end slash
            this._Url = this._Url.replace(/\/?$/, '/');
            this._AbsoluteUrl = this._AbsoluteUrl.replace(/\/?$/, '/');
        },

        /**
         *
         * @returns {boolean}
         */
        IsFolder: function() {
            return true;
        },

        /**
         * Creates a new folder with a specified name as child of this folder.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {string} sName Name of the new folder.
         * @param {string} [sLockTokens] Lock token for ITHit.WebDAV.Client.Folder folder.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. Default is empty array.
         * @returns {ITHit.WebDAV.Client.Folder} Created folder object.
         * @throws ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException Item with specified name already exists.
         * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException Creation of child items not allowed.
         * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This folder doesn't exist on the server.
         * @throws ITHit.WebDAV.Client.Exceptions.LockedException This folder is locked and no or invalid lock token was specified.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknow error.
         */
        CreateFolder: function(sName, sLockTokens, aProperties) {
			aProperties = aProperties || [];

            // Start logging.
            var oRequest = this.Session.CreateRequest(this.__className + '.CreateFolder()', 2);

            // Set default value if needed.
            sLockTokens = sLockTokens || null;

            // Get URI for new folder.
            var sNewUri = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName);

            // Create folder.
            var oResponse = ITHit.WebDAV.Client.Methods.Mkcol.Go(oRequest, sNewUri, sLockTokens, this.Host).Response;

            // Whether folder is not created.
            if (!oResponse.Status.Equals(ITHit.WebDAV.Client.HttpStatus.Created)) {
                oRequest.MarkFinish();
                throw new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(ITHit.Phrases.Exceptions.FailedCreateFolder, sNewUri, null, oResponse.Status, null);
            }

            // Return created folder object.
            var oFolder = ITHit.WebDAV.Client.Folder.OpenItem(oRequest, ITHit.WebDAV.Client.Encoder.DecodeURI(sNewUri), aProperties);

            oRequest.MarkFinish();
            return oFolder;
        },

        /**
         * Callback function to be called when a folder is created on the server.
         * @callback ITHit.WebDAV.Client.Folder~CreateFolderAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.Folder} oResult.Result Created folder object.
         */

        /**
         * Creates a new folder with a specified name as child of this folder.
         * @api
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.CreateFolder.CreateFolder
         * @param {string} sName Name of the new folder.
         * @param {string} [sLockTokens] Lock token for ITHit.WebDAV.Client.Folder folder.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. Default is empty array.
         * @param {ITHit.WebDAV.Client.Folder~CreateFolderAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        CreateFolderAsync: function (sName, sLockTokens, aProperties, fCallback) {
			aProperties = aProperties || [];

            var oRequest = this.Session.CreateRequest(this.__className + '.CreateFolderAsync()', 2);

            var sNewUri = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName);
            ITHit.WebDAV.Client.Methods.Mkcol.GoAsync(oRequest, sNewUri, sLockTokens, this.Host, function(oAsyncResult) {

                // Whether folder is not created.
                if (oAsyncResult.IsSuccess && !oAsyncResult.Result.Response.Status.Equals(ITHit.WebDAV.Client.HttpStatus.Created)) {
                    oAsyncResult.IsSuccess = false;
                    oAsyncResult.Error = new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(
                        ITHit.Phrases.Exceptions.FailedCreateFolder,
                        sNewUri,
                        null,
                        oAsyncResult.Result.Response.Status
                    );
                }

                if (oAsyncResult.IsSuccess) {
                    self.OpenItemAsync(oRequest, sNewUri, aProperties, function(oAsyncResult) {

                        oRequest.MarkFinish();
                        fCallback(oAsyncResult);
                    });
                } else {
                    oAsyncResult.Result = null;

                    oRequest.MarkFinish();
                    fCallback(oAsyncResult);
                }
            });

            return oRequest;
        },

        /**
         * Creates a new file with a specified name as a child of this folder.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {string} sName Name of the new file.
         * @param {string} [sLockTokens] Lock token for current folder.
         * @param {string} [sContent] File content.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. Default is empty array.
         * @returns {ITHit.WebDAV.Client.File} Created file object.
         * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException Creation of child items not allowed.
         * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This folder doesn't exist on the server.
         * @throws ITHit.WebDAV.Client.Exceptions.LockedException This folder is locked and no or invalid lock token was specified.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
         */
        CreateFile: function(sName, sLockTokens, sContent, aProperties) {
            sLockTokens = sLockTokens || null;
            sContent = sContent || '';
			aProperties = aProperties || [];

            var oRequest = this.Session.CreateRequest(this.__className + '.CreateFile()', 2);

            // Get URI for new folder.
            var sNewUri = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName);

            // Create file.
            var oResult = ITHit.WebDAV.Client.Methods.Put.Go(
                oRequest,
                sNewUri,
                '',
                sContent,
                sLockTokens,
                this.Host
            );

            var oError = this._GetErrorFromCreateFileResponse(oResult.Response, sNewUri);
            if (oError) {
                oRequest.MarkFinish();
                throw oError;
            }

            // Return created file object.
            var oFile = ITHit.WebDAV.Client.File.OpenItem(oRequest, sNewUri, aProperties);

            oRequest.MarkFinish();
            return oFile;
        },

        /**
         * Callback function to be called when a file is created on the server.
         * @callback ITHit.WebDAV.Client.Folder~CreateFileAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.File} oResult.Result Created file object.
         */

        /**
         * Creates a new file with a specified name as a child of this folder.
         * @api
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.CreateFile.CreateAndWriteContent
         * @param {string} sName Name of the new file.
         * @param {string} sLockTokens Lock token for current folder.
         * @param {string} sContent File content.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. Default is empty array.
         * @param {ITHit.WebDAV.Client.Folder~CreateFileAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        CreateFileAsync: function(sName, sLockTokens, sContent, aProperties, fCallback) {
            sLockTokens = sLockTokens || null;
            sContent = sContent || '';
			aProperties = aProperties || [];

            var oRequest = this.Session.CreateRequest(this.__className + '.CreateFileAsync()', 2);

            // Get URI for new folder.
            var sNewUri = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName);

            var that = this;
            ITHit.WebDAV.Client.Methods.Put.GoAsync(
                oRequest,
                sNewUri,
                '',
                sContent,
                sLockTokens,
                this.Host,
                function(oAsyncResult) {
                    if (oAsyncResult.IsSuccess) {
                        oAsyncResult.Error = that._GetErrorFromCreateFileResponse(oAsyncResult.Result.Response);
                        if (oAsyncResult.Error !== null) {
                            oAsyncResult.IsSuccess = false;
                            oAsyncResult.Result = null;
                        }
                    }

                    if (oAsyncResult.IsSuccess) {
                        ITHit.WebDAV.Client.File.OpenItemAsync(oRequest, sNewUri, aProperties, function(oAsyncResult) {

                            oRequest.MarkFinish();
                            fCallback(oAsyncResult);
                        });
                    } else {

                        oRequest.MarkFinish();
                        fCallback(oAsyncResult);
                    }
                }
            );

            return oRequest;
        },

        /**
         * Legacy proxy to CreateFile() method
         * @private
         * @deprecated
         * @param sName
         * @param sLockTokens
         * @param sContent
         */
        CreateResource: function(sName, sLockTokens,  sContent, aProperties) {
            return this.CreateFile(sName, sLockTokens, sContent, aProperties);
        },

        /**
         * Legacy proxy to CreateFileAsync() method
         * @private
         * @deprecated
         * @param sName
         * @param sLockTokens
         * @param sContent
         * @param fCallback
         */
        CreateResourceAsync: function(sName, sLockTokens, sContent, aProperties, fCallback) {
            return this.CreateFileAsync(sName, sLockTokens, sContent, aProperties, fCallback);
        },

        /**
         * Locks name for later use.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {string} sNewItemName Name of new item.
         * @param {string} sLockScope Scope of the lock.
         * @param {boolean} bDeep Whether to lock entire subtree.
         * @param {string} sOwner Owner of the lock.
         * @param {number} iTimeout TimeOut after which lock expires.
         * @returns {ITHit.WebDAV.Client.LockInfo} Instance of LockInfo object with information about created lock.
         * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This folder doesn't exist on the server.(Server in fact returns Conflict)
         * @throws ITHit.WebDAV.Client.Exceptions.LockedException This folder is locked and no or invalid lock token was specified.
         * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException The client, for reasons the server chooses not to specify, cannot apply the lock.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
         */
        CreateLockNull: function(sNewItemName, sLockScope, bDeep, sOwner, iTimeout) {

            var oRequest = this.Session.CreateRequest(this.__className + '.CreateLockNull()');

            // Get new URI.
            var sNewUri = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sNewItemName);

            // Make request.
            var oResult = ITHit.WebDAV.Client.Methods.Lock.Go(
                oRequest,
                sNewUri,
                iTimeout,
                sLockScope,
                this.Host,
                bDeep,
                sOwner
            );

            oRequest.MarkFinish();

            // Return lock info.
            return oResult.LockInfo;
        },

        /**
         * This method returns all items contained in the folder, which may be very large. To limit amount of items returned and get only a single results page use [GetPageAsync]{@link ITHit.WebDAV.Client.Folder#GetPageAsync} function instead.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {boolean} [bRecursively] Indicates if all subtree of children should be return. Default is false.
         * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. If null is specified, only default properties are returned.
         * @returns {ITHit.WebDAV.Client.HierarchyItem[]} Array of file and folder objects.
         * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException This folder doesn't exist on the server.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavHttpException Server returned unknown error.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
         */
        GetChildren: function(bRecursively, aProperties) {
            bRecursively = bRecursively || false;
            aProperties = aProperties || [];

            var oRequest = this.Session.CreateRequest(this.__className + '.GetChildren()');

            var aCustomProperties = ITHit.WebDAV.Client.HierarchyItem.GetCustomRequestProperties(aProperties);
            var aAllProperties = aCustomProperties.concat(ITHit.WebDAV.Client.HierarchyItem.GetRequestProperties());

            // Make response.
            var oResult = ITHit.WebDAV.Client.Methods.Propfind.Go(
                oRequest,
                this.Href,
                ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
                aAllProperties,
                bRecursively ? ITHit.WebDAV.Client.Depth.Infinity : ITHit.WebDAV.Client.Depth.One,
                this.Host
            );

            var aItems = ITHit.WebDAV.Client.HierarchyItem.GetItemsFromMultiResponse(oResult.Response, oRequest, this.Href, aCustomProperties);

            oRequest.MarkFinish();
            return aItems;
        },

        /**
         * Callback function to be called when children items loaded from server.
         * @callback ITHit.WebDAV.Client.Folder~GetPageAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.PageResults} oResult.Result sinle page results.
         */

        /**
         * Gets specified number of children of this folder that correspond to requested offset and sorting. Use GetSupportedFeaturesAsync() function to detect if paging is supported.
         * @api      
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.GetFolderItems.GetPage
         * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. If null is specified, only default properties are returned.      
         * @param {number} [nOffset] The number of items to skip before returning the remaining items.
         * @param {number} [nResults] The number of items to return.
         * @param {ITHit.WebDAV.Client.OrderProperty[]} [aOrderProperties] List of order properties.
         * @param {ITHit.WebDAV.Client.Folder~GetPageAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.       
         */
        GetPageAsync: function (aProperties, nOffset, nResults, aOrderProperties, fCallback) {
            aOrderProperties = aOrderProperties || [];
            if (typeof aProperties === 'function') {
                fCallback = aProperties;
                aProperties = [];
            } else {
                aProperties = aProperties || [];
                fCallback = fCallback || function() {};
            }

            var oRequest = this.Session.CreateRequest(this.__className + '.GetPageAsync()');

            var aCustomProperties = ITHit.WebDAV.Client.HierarchyItem.GetCustomRequestProperties(aProperties);
            var aAllProperties = aCustomProperties.concat(ITHit.WebDAV.Client.HierarchyItem.GetRequestProperties());

            // Make response.
            var that = this;
            ITHit.WebDAV.Client.Methods.Propfind.GoAsync(
                oRequest,
                this.Href,
                ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
                aAllProperties,
                ITHit.WebDAV.Client.Depth.One,
                this.Host,
                function(oAsyncResult) {
                    if (oAsyncResult.IsSuccess) {
                        oAsyncResult.Result = new ITHit.WebDAV.Client.PageResults(ITHit.WebDAV.Client.HierarchyItem.GetItemsFromMultiResponse(oAsyncResult.Result.Response, oRequest, that.Href, aCustomProperties), oAsyncResult.Result.Response.TotalItems);
                    }

                    oRequest.MarkFinish();
                    fCallback(oAsyncResult);
                },
                nOffset, nResults, aOrderProperties
            );

            return oRequest;
        },

        /**
         * Callback function to be called when children items loaded from server.
         * @callback ITHit.WebDAV.Client.Folder~GetChildrenAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.HierarchyItem[]} oResult.Result Array of file and folder objects.
         */

        /**
         * This method returns all items contained in the folder, which may be very large. To limit amount of items returned and get only a single results page use [GetPageAsync]{@link ITHit.WebDAV.Client.Folder#GetPageAsync} function instead.
         * @api
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.GetFolderItems.GetChildrenAsync
         * @param {boolean} bRecursively Indicates if all subtree of children should be return. Default is false.
         * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. If null is specified, only default properties are returned.
         * @param {ITHit.WebDAV.Client.Folder~GetChildrenAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        GetChildrenAsync: function (bRecursively, aProperties, fCallback) { 
            bRecursively = bRecursively || false;
            if (typeof aProperties === 'function') {
                fCallback = aProperties;
                aProperties = [];
            } else {
                aProperties = aProperties || [];
                fCallback = fCallback || function () { };
            }

            var oRequest = this.Session.CreateRequest(this.__className + '.GetChildrenAsync()');

            var aCustomProperties = ITHit.WebDAV.Client.HierarchyItem.GetCustomRequestProperties(aProperties);
            var aAllProperties = aCustomProperties.concat(ITHit.WebDAV.Client.HierarchyItem.GetRequestProperties());

            // Make response.
            var that = this;
            ITHit.WebDAV.Client.Methods.Propfind.GoAsync(
                oRequest,
                this.Href,
                ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
                aAllProperties,
                bRecursively ? ITHit.WebDAV.Client.Depth.Infinity : ITHit.WebDAV.Client.Depth.One,
                this.Host,
                function (oAsyncResult) {
                    if (oAsyncResult.IsSuccess) {
                        oAsyncResult.Result = ITHit.WebDAV.Client.HierarchyItem.GetItemsFromMultiResponse(oAsyncResult.Result.Response, oRequest, that.Href, aCustomProperties);
                    }

                    oRequest.MarkFinish();
                    fCallback(oAsyncResult);
                },
                null, null, null
            );

            return oRequest;
        },

        /**
         * Gets the specified folder from server.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {string} sName Name of the folder.
         * @returns {ITHit.WebDAV.Client.Folder} Folder object corresponding to requested path.
         * @throws ITHit.WebDAV.Client.Exceptions.UnauthorizedException Incorrect credentials provided or insufficient permissions to access the requested item.
         * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException The requested folder doesn't exist on the server.
         * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException The server refused to fulfill the request.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
         */
        GetFolder: function(sName) {
            var oRequest = this.Session.CreateRequest(this.__className + '.GetFolder()');
            var sHref = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName);
            var oFolder = self.OpenItem(oRequest, sHref);

            oRequest.MarkFinish();
            return oFolder;
        },

        /**
         * Callback function to be called when folder loaded from server.
         * @callback ITHit.WebDAV.Client.Folder~GetFolderAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.Folder} oResult.Result Folder object corresponding to requested path.
         */

        /**
         * Gets the specified folder from server.
         * @api
         * @param {string} sName Name of the folder.
         * @param {ITHit.WebDAV.Client.Folder~GetFolderAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        GetFolderAsync: function(sName, fCallback) {
            var oRequest = this.Session.CreateRequest(this.__className + '.GetFolderAsync()');
            var sHref = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName);
            self.OpenItemAsync(oRequest, sHref, null, function(oAsyncResult) {

                oRequest.MarkFinish();
                fCallback(oAsyncResult);
            });

            return oRequest;
        },

        /**
         * Gets the specified file from server.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {string} sName Name of the file.
         * @returns {ITHit.WebDAV.Client.File} File corresponding to requested path.
         * @throws ITHit.WebDAV.Client.Exceptions.UnauthorizedException Incorrect credentials provided or insufficient permissions to access the requested item.
         * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException The requested file doesn't exist on the server.
         * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException The server refused to fulfill the request.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
         */
        GetFile: function(sName) {
            var oRequest = this.Session.CreateRequest(this.__className + '.GetFile()');
            var sHref = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName);
            var oFile = ITHit.WebDAV.Client.File.OpenItem(oRequest, sHref);

            oRequest.MarkFinish();
            return oFile;
        },

        /**
         * Callback function to be called when file loaded from server.
         * @callback ITHit.WebDAV.Client.Folder~GetFileAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.File} oResult.Result File corresponding to requested path.
         */

        /**
         * Gets the specified file from server.
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.GetItemByFolder.GetFile
         * @api
         * @param {string} sName Name of the file.
         * @param {ITHit.WebDAV.Client.Folder~GetFileAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        GetFileAsync: function(sName, fCallback) {
            var oRequest = this.Session.CreateRequest(this.__className + '.GetFileAsync()');
            var sHref = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName);
            ITHit.WebDAV.Client.File.OpenItemAsync(oRequest, sHref, null, function(oAsyncResult) {

                oRequest.MarkFinish();
                fCallback(oAsyncResult);
            });

            return oRequest;
        },

        /**
         * Legacy proxy to GetFile() method
         * @private
         * @deprecated
         * @param sName
         */
        GetResource: function(sName) {
            return this.GetFile(sName);
        },

        /**
         * Legacy proxy to GetFileAsync() method
         * @private
         * @deprecated
         * @param sName
         * @param fCallback
         */
        GetResourceAsync: function(sName, fCallback) {
            return this.GetFileAsync(sName, fCallback);
        },

        /**
         * Gets the specified item from server.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {string} sName Name of the item.
         * @returns {ITHit.WebDAV.Client.HierarchyItem} Item object corresponding to requested path.
         * @throws ITHit.WebDAV.Client.Exceptions.UnauthorizedException Incorrect credentials provided or insufficient permissions to access the requested item.
         * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException The requested folder doesn't exist on the server.
         * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException The server refused to fulfill the request.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
         */
        GetItem: function(sName) {
            var oRequest = this.Session.CreateRequest(this.__className + '.GetItem()');
            var sHref = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName);
            var oItem = ITHit.WebDAV.Client.HierarchyItem.OpenItem(oRequest, sHref);

            oRequest.MarkFinish();
            return oItem;
        },

        /**
         * Callback function to be called when item loaded from server.
         * @callback ITHit.WebDAV.Client.Folder~GetItemAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.HierarchyItem} oResult.Result Item object corresponding to requested path.
         */

        /**
         * Gets the specified item from server.
         * @api
         * @param {string} sName Name of the item.
         * @param {ITHit.WebDAV.Client.Folder~GetItemAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        GetItemAsync: function(sName, fCallback) {
            var oRequest = this.Session.CreateRequest(this.__className + '.GetItemAsync()');
            var sHref = ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName);
            ITHit.WebDAV.Client.HierarchyItem.OpenItemAsync(oRequest, sHref, null, function(oAsyncResult) {

                oRequest.MarkFinish();
                fCallback(oAsyncResult);
            });

            return oRequest;
        },

        /**
         * Checks whether specified item exists in the folder.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {string} sName Name of the item.
         * @returns {boolean} Returns true, if specified item exists; false, otherwise.
         */
        ItemExists: function(sName) {

            var oRequest = this.Session.CreateRequest(this.__className + '.ItemExists()', 2);

            try {
                // Try to make HEAD request.
                var oResult = ITHit.WebDAV.Client.Methods.Head.Go(
                    oRequest,
                    ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName),
                    this.Host
                );
            } catch (oError) {

                // If method is not allowed exception is raised.
                if (oError instanceof ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException) {

                    try {
                        // Try to make PROPFIND request.
                        ITHit.WebDAV.Client.Methods.Propfind.Go(
                            oRequest,
                            ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName),
                            ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
                            [
                                ITHit.WebDAV.Client.DavConstants.DisplayName
                            ],
                            ITHit.WebDAV.Client.Depth.Zero,
                            this.Host
                        );
                    } catch (oSubError) {
                        // Whether file not found.
                        if (oSubError instanceof ITHit.WebDAV.Client.Exceptions.NotFoundException) {
                            oRequest.MarkFinish();
                            return false;
                        }

                        // Rethrow exception for all other cases.
                        throw oSubError;
                    }

                    // Item is found.
                    oRequest.MarkFinish();
                    return true;
                }

                // Rethrow exception.
                throw oError;
            }

            oRequest.MarkFinish();
            return oResult.IsOK;
        },

        /**
         * Callback function to be called when check request is complete.
         * @callback ITHit.WebDAV.Client.Folder~ItemExistsAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {boolean} oResult.Result Returns true, if specified item exists; false, otherwise.
         */

        /**
         * Checks whether specified item exists in the folder.
         * @api
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.ItemExists.ItemExists
         * @param {string} sName Name of the item.
         * @param {ITHit.WebDAV.Client.Folder~ItemExistsAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        ItemExistsAsync: function(sName, fCallback) {

            var oRequest = this.Session.CreateRequest(this.__className + '.ItemExistsAsync()', 2);

            // Try to make HEAD request.
            var that = this;
            ITHit.WebDAV.Client.Methods.Head.GoAsync(
                oRequest,
                ITHit.WebDAV.Client.HierarchyItem.AppendToUri(this.Href, sName),
                this.Host,
                function(oAsyncResult) {
                    if (oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException) {

                        // Try to make PROPFIND request.
                        ITHit.WebDAV.Client.Methods.Propfind.GoAsync(
                            oRequest,
                            ITHit.WebDAV.Client.HierarchyItem.AppendToUri(that.Href, sName),
                            ITHit.WebDAV.Client.Methods.Propfind.PropfindMode.SelectedProperties,
                            [
                                ITHit.WebDAV.Client.DavConstants.DisplayName
                            ],
                            ITHit.WebDAV.Client.Depth.Zero,
                            that.Host,
                            function(oSubAsyncResult) {
                                oSubAsyncResult.Result = oSubAsyncResult.IsSuccess;

                                if (oSubAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.NotFoundException) {
                                    oSubAsyncResult.IsSuccess = true;
                                    oSubAsyncResult.Result = false;
                                }

                                oRequest.MarkFinish();
                                fCallback(oSubAsyncResult);
                            }
                        );
                        return;
                    }

                    oAsyncResult.Result = oAsyncResult.Result.IsOK;

                    oRequest.MarkFinish();
                    fCallback(oAsyncResult);
                }
            );

            return oRequest;
        },

        /**
         * Searches folder by query.
         * @private
         * @deprecated Use asynchronous method instead.
         * @param {ITHit.WebDAV.Client.SearchQuery} oSearchQuery Object with search query conditions.
         * @returns {ITHit.WebDAV.Client.HierarchyItem[]}
         */
        SearchByQuery: function(oSearchQuery) {

            var oRequest = this.Session.CreateRequest(this.__className + '.SearchByQuery()');

            var aCustomProperties = ITHit.WebDAV.Client.HierarchyItem.GetCustomRequestProperties(oSearchQuery.SelectProperties);
            oSearchQuery.SelectProperties = aCustomProperties.concat(ITHit.WebDAV.Client.HierarchyItem.GetRequestProperties());

            var oResult = ITHit.WebDAV.Client.Methods.Search.Go(
                oRequest,
                this.Href,
                this.Host,
                oSearchQuery
            );

            var aItems = ITHit.WebDAV.Client.HierarchyItem.GetItemsFromMultiResponse(oResult.Response, oRequest, this.Href, aCustomProperties);

            oRequest.MarkFinish();
            return aItems;
        },

        /**
         * Callback function to be called when search is complete and items are loaded from server.
         * @callback ITHit.WebDAV.Client.Folder~SearchByQueryAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.HierarchyItem[]} oResult.Result Array of file objects.
         */

        /**
         * This method returns all items found on the server, which may be very large. To limit amount of items returned and get only a single results page use [GetSearchPageByQueryAsync]{@link ITHit.WebDAV.Client.Folder#GetSearchPageByQueryAsync} function instead.
         * @api
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.Search.SearchByQuery
         * @param {ITHit.WebDAV.Client.SearchQuery} oSearchQuery Object with search query conditions.
         * @param {ITHit.WebDAV.Client.Folder~SearchByQueryAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        SearchByQueryAsync: function(oSearchQuery, fCallback) {

            return this.GetSearchPageByQueryAsync(oSearchQuery, null, null, fCallback);
        },


        /**
         * Callback function to be called when search is complete and items are loaded from server.
         * @callback ITHit.WebDAV.Client.Folder~GetSearchPageByQueryAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.PageResults} oResult.Result sinle page results.
         */

        /**
         * Searches folder by query. Returns specified number of search result items that correspond to requested offset and sorting. Use GetSupportedFeaturesAsync() function to detect if paging is supported.
         * @api
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.Search.GetSearchPageByQuery
         * @param {ITHit.WebDAV.Client.SearchQuery} oSearchQuery Object with search query conditions.
         * @param {number} [nOffset] The number of items to skip before returning the remaining items.
         * @param {number} [nResults] The number of items to return.
         * @param {ITHit.WebDAV.Client.Folder~GetSearchPageByQueryAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        GetSearchPageByQueryAsync: function (oSearchQuery, nOffset, nResults, fCallback) {

            var oRequest = this.Session.CreateRequest(this.__className + '.GetSearchPageByQueryAsync()');

            var aCustomProperties = ITHit.WebDAV.Client.HierarchyItem.GetCustomRequestProperties(oSearchQuery.SelectProperties);
            oSearchQuery.SelectProperties = aCustomProperties.concat(ITHit.WebDAV.Client.HierarchyItem.GetRequestProperties());

            var that = this;
            ITHit.WebDAV.Client.Methods.Search.GoAsync(
                oRequest,
                this.Href,
                this.Host,
                oSearchQuery,
                function (oAsyncResult) {
                    if (oAsyncResult.IsSuccess) {
                        if (nOffset != null) {
                            oAsyncResult.Result = new ITHit.WebDAV.Client.PageResults(ITHit.WebDAV.Client.HierarchyItem.GetItemsFromMultiResponse(oAsyncResult.Result.Response, oRequest, that.Href, aCustomProperties), oAsyncResult.Result.Response.TotalItems);
                        }
                        else {
                            oAsyncResult.Result = ITHit.WebDAV.Client.HierarchyItem.GetItemsFromMultiResponse(oAsyncResult.Result.Response, oRequest, that.Href, aCustomProperties);
                        }
                    }

                    oRequest.MarkFinish();
                    fCallback(oAsyncResult);
                },
                nOffset, nResults
            );

            return oRequest;
        },

        /**
         * This method returns all items found on the server, which may be very large. To limit amount of items returned and get only a single results page use [GetSearchPageAsync]{@link ITHit.WebDAV.Client.Folder#GetSearchPageAsync} function instead.
         * @private
         * @deprecated Use asynchronous method instead.
         * @param {string} sSearchQuery String of search query.
         * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. If null is specified, only default properties are returned.
         * @returns {ITHit.WebDAV.Client.HierarchyItem[]}
         */
        Search: function (sSearchQuery, aProperties) {
            var oSearchQuery = new ITHit.WebDAV.Client.SearchQuery(sSearchQuery);
            oSearchQuery.SelectProperties = aProperties || [];

            return this.SearchByQuery(oSearchQuery);
        },

        /**
         * Callback function to be called when search is complete and items are loaded from server.
         * @callback ITHit.WebDAV.Client.Folder~SearchAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object.
         * @param {ITHit.WebDAV.Client.HierarchyItem[]} oResult.Result Array of file objects.
         */

        /**
         * Searches folder by search string. To limit amount of items returned and get only a single results page use [GetSearchPageAsync]{@link ITHit.WebDAV.Client.Folder#GetSearchPageAsync} function instead.
         * @api
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.Search.SearchByString
         * @param {string} sSearchQuery String of search query.
         * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. If null is specified, only default properties are returned.
         * @param {ITHit.WebDAV.Client.Folder~SearchAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        SearchAsync: function (sSearchQuery, aProperties, fCallback) {
            var oSearchQuery = new ITHit.WebDAV.Client.SearchQuery(sSearchQuery);
            oSearchQuery.SelectProperties = aProperties || [];

            return this.SearchByQueryAsync(oSearchQuery, fCallback);
        },

        /**
        * Callback function to be called when search is complete and items are loaded from server.
        * @callback ITHit.WebDAV.Client.Folder~GetSearchPageAsyncCallback
        * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
        * @param {ITHit.WebDAV.Client.PageResults} oResult.Result sinle page results.
        */

        /**
         * Searches folder by search string. Returns specified number of search result items that correspond to requested offset and sorting. Use GetSupportedFeaturesAsync() function to detect if paging is supported.
         * @api
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.Search.GetSearchPageByString
         * @param {string} sSearchQuery String of search query.
         * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. If null is specified, only default properties are returned.
         * @param {number} [nOffset] The number of items to skip before returning the remaining items.
         * @param {number} [nResults] The number of items to return.
         * @param {ITHit.WebDAV.Client.Folder~GetSearchPageAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        GetSearchPageAsync: function (sSearchQuery, aProperties, nOffset, nResults, fCallback) {
            var oSearchQuery = new ITHit.WebDAV.Client.SearchQuery(sSearchQuery);
            oSearchQuery.SelectProperties = aProperties || [];

            return this.GetSearchPageByQueryAsync(oSearchQuery, nOffset, nResults, fCallback);
        },

        _GetErrorFromCreateFileResponse: function(oResponse, sNewUri) {
            // Whether folder is not created.
            if (!oResponse.Status.Equals(ITHit.WebDAV.Client.HttpStatus.Created) && !oResponse.Status.Equals(ITHit.WebDAV.Client.HttpStatus.OK)) {
                return new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(ITHit.Phrases.Exceptions.FailedCreateFile, sNewUri, null, oResponse.Status, null);
            }

            return null;
        }

    });

})();

;
(function () {

	/**
	 * @class ITHit.WebDAV.Client.Methods.UpdateToVersion
	 * @extends ITHit.WebDAV.Client.Methods.HttpMethod
	 */
	var self = ITHit.DefineClass('ITHit.WebDAV.Client.Methods.UpdateToVersion', ITHit.WebDAV.Client.Methods.HttpMethod, /** @lends ITHit.WebDAV.Client.Methods.UpdateToVersion.prototype */{

		__static: /** @lends ITHit.WebDAV.Client.Methods.UpdateToVersion */{

			Go: function (oRequest, sHref, sHost, sToVersionHref) {

				// Create request.
				var oWebDavRequest = this.createRequest(oRequest, sHref, sHost, sToVersionHref);

				// Make request.
				var oResponse = oWebDavRequest.GetResponse();

				return this._ProcessResponse(oResponse, sHref);
			},

			GoAsync: function (oRequest, sHref, sHost, sToVersionHref, fCallback) {

				// Create request.
				var oWebDavRequest = this.createRequest(oRequest, sHref, sHost, sToVersionHref);

				// Make request.
				var that = this;
				oWebDavRequest.GetResponse(function (oAsyncResult) {
					if (!oAsyncResult.IsSuccess) {
						fCallback(new ITHit.WebDAV.Client.AsyncResult(null, false, oAsyncResult.Error));
						return;
					}

					var oResult = that._ProcessResponse(oAsyncResult.Result, sHref);
					fCallback(new ITHit.WebDAV.Client.AsyncResult(oResult, true, null));
				});

				return oWebDavRequest;
			},

			_ProcessResponse: function (oResponse, sHref) {

				// Receive data.
				var oResponseData = oResponse.GetResponseStream();
				return new self(new ITHit.WebDAV.Client.Methods.MultiResponse(oResponseData, sHref));
			},

			createRequest: function (oRequest, sHref, sHost, sToVersionHref) {

				var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref);

				oWebDavRequest.Method('UPDATE');
				oWebDavRequest.Headers.Add('Content-Type', 'text/xml; charset="utf-8"');

				// Create XML DOM document.
				var oWriter = new ITHit.XMLDoc();

				// Get namespace for XML elements.
				var sNamespaceUri = ITHit.WebDAV.Client.DavConstants.NamespaceUri;

				// Create elements.
				var oUpdateElement = oWriter.createElementNS(sNamespaceUri, 'update');
				var oVersionElement = oWriter.createElementNS(sNamespaceUri, 'version');
				var oHrefElement = oWriter.createElementNS(sNamespaceUri, 'href');

				// Set value
				oHrefElement.appendChild(oWriter.createTextNode(sToVersionHref));

				// Append created child nodes.
				oVersionElement.appendChild(oHrefElement);
				oUpdateElement.appendChild(oVersionElement);
				oWriter.appendChild(oUpdateElement);

				oWebDavRequest.Body(oWriter);

				// Return request object.
				return oWebDavRequest;
			}

		}
	});

})();

;
(function() {

	/**
	 * Represents a version on a WebDAV server.
	 * @class ITHit.WebDAV.Client.Version
	 * @extends ITHit.WebDAV.Client.File
	 */
	var self = ITHit.DefineClass('ITHit.WebDAV.Client.Version', ITHit.WebDAV.Client.File, /** @lends ITHit.WebDAV.Client.Version.prototype */{

		__static: /** @lends ITHit.WebDAV.Client.Version */{

			GetRequestProperties: function() {
				return [
					ITHit.WebDAV.Client.DavConstants.DisplayName,
					ITHit.WebDAV.Client.DavConstants.CreationDate,
					ITHit.WebDAV.Client.DavConstants.GetContentType,
					ITHit.WebDAV.Client.DavConstants.GetContentLength,
					ITHit.WebDAV.Client.DavConstants.VersionName,
					ITHit.WebDAV.Client.DavConstants.CreatorDisplayName,
					ITHit.WebDAV.Client.DavConstants.Comment
				];
			},

			/**
			 * Get version name from response.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @returns {string} Version name.
			 */
			GetVersionName: function(oResponse) {
				var oValue = ITHit.WebDAV.Client.HierarchyItem.GetProperty(oResponse, ITHit.WebDAV.Client.DavConstants.VersionName).Value;
				if (oValue.hasChildNodes()) {
					return oValue.firstChild().nodeValue();
				}
				return null;
			},

			/**
			 * Get creator user name from response.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @returns {string} Creator name.
			 */
			GetCreatorDisplayName: function(oResponse) {
				var oValue = ITHit.WebDAV.Client.HierarchyItem.GetProperty(oResponse, ITHit.WebDAV.Client.DavConstants.CreatorDisplayName).Value;
				if (oValue.hasChildNodes()) {
					return oValue.firstChild().nodeValue();
				}
				return null;
			},

			/**
			 * Get comment string from response.
			 * @param {ITHit.WebDAV.Client.WebDavResponse} oResponse Response object.
			 * @returns {string} Comment string.
			 */
			GetComment: function(oResponse) {
				var oValue = ITHit.WebDAV.Client.HierarchyItem.GetProperty(oResponse, ITHit.WebDAV.Client.DavConstants.Comment).Value;
				if (oValue.hasChildNodes()) {
					return oValue.firstChild().nodeValue();
				}
				return null;
			},

			GetVersionsFromMultiResponse: function(oResponses, oFile) {
				var aVersionList = [];

				for (var i = 0; i < oResponses.length; i++) {
					var oResponse = oResponses[i];

					aVersionList.push(new self(
						oFile.Session,
						oResponse.Href,
						oFile,
						this.GetDisplayName(oResponse),
						this.GetVersionName(oResponse),
						this.GetCreatorDisplayName(oResponse),
						this.GetComment(oResponse),
						this.GetCreationDate(oResponse),
						this.GetContentType(oResponse),
						this.GetContentLength(oResponse),
						oFile.Host,
						this.GetPropertiesFromResponse(oResponse)
					));
				}

				// Sort versions by version number (other symbols is skipped)
				aVersionList.sort(function(a, b) {
					var aVersionNumber = parseInt(a.VersionName.replace(/[^0-9]/g, ''));
					var bVersionNumber = parseInt(b.VersionName.replace(/[^0-9]/g, ''));

					if (aVersionNumber === bVersionNumber) {
						return 0;
					}
					return aVersionNumber > bVersionNumber ? 1 : -1;
				});

				return aVersionList;
			},

			ParseSetOfHrefs: function(aProperties) {
				var aUrls = [];

				for (var i = 0, l = aProperties.length; i < l; i++) {
					var xml = aProperties[i].Value;
					var aXmlHrefs = xml.getElementsByTagNameNS(ITHit.WebDAV.Client.DavConstants.NamespaceUri, 'href');

					for (var i2 = 0, l2 = aXmlHrefs.length; i2 < l2; i2++) {
						aUrls.push(aXmlHrefs[i2].firstChild().nodeValue());
					}
				}

				return aUrls;
			},
			
			/**
			 * Compares two software version numbers (e.g. "1.7.1" or "1.2").
			 *
			 * @param {string} v1 The first version to be compared.
			 * @param {string} v2 The second version to be compared.
			 * @returns {number}
			 * <ul>
			 *    <li>0 if the versions are equal</li>
			 *    <li>a negative integer iff v1 < v2</li>
			 *    <li>a positive integer iff v1 > v2</li>
			 * </ul>
			 */
			VersionCompare: function(v1, v2) {
				if (v1 == null) v1 = '0';
				if (v2 == null) v2 = '0';
				var v1parts = v1.split('.'),
					v2parts = v2.split('.');

				// Zero extend
				while (v1parts.length < v2parts.length) v1parts.push("0");
				while (v2parts.length < v1parts.length) v2parts.push("0");

				v1parts = v1parts.map(Number);
				v2parts = v2parts.map(Number);

				for (var i = 0; i < v1parts.length; ++i) {
					if (v2parts.length == i) {
						return 1;
					}

					if (v1parts[i] == v2parts[i]) {
						continue;
					}
					else if (v1parts[i] > v2parts[i]) {
						return 1;
					}
					else {
						return -1;
					}
				}

				if (v1parts.length != v2parts.length) {
					return -1;
				}
				return 0;
			}
		},

		/**
		 * This property contains a server-defined string that is different for each version.
		 * This string is intended for display for a user.
		 * @api
		 * @type {string}
		 */
		VersionName: null,

		/**
		 *
		 * @type {string}
		 */
		CreatorDisplayName: null,

		/**
		 *
		 * @type {string}
		 */
		Comment: null,

		/**
		 *
		 * @type {ITHit.WebDAV.Client.File}
		 */
		_File: null,

		/**
		 * @type {null}
		 */
		ResumableUpload: null,

		/**
		 * @type {null}
		 */
		LastModified: null,

		/**
		 * @type {null}
		 */
		ActiveLocks: null,

		/**
		 * @type {null}
		 */
		AvailableBytes: null,

		/**
		 * @type {null}
		 */
		UsedBytes: null,

		/**
		 * @type {null}
		 */
		VersionControlled: null,

		/**
		 * @type {null}
		 */
		ResourceType: null,

		/**
		 * @type {null}
		 */
		SupportedLocks: null,

		/**
		 * Create new instance of Version class which represents a version on a WebDAV server.
		 * @param {ITHit.WebDAV.Client.WebDavSession} oSession Current WebDAV session.
		 * @param {string} sHref This item path on the server.
		 * @param {ITHit.WebDAV.Client.File} oFile File instance.
		 * @param {string} sDisplayName User friendly item name.
		 * @param {string} sVersionName User friendly version name.
		 * @param {string} sCreatorDisplayName Creator user name.
		 * @param {string} sComment Comment string.
		 * @param {object} oCreationDate The date item was created.
		 * @param {string} sContentType Content type.
		 * @param {number} iContentLength Content length.
		 * @param {string} sHost
		 * @param {object} oProperties
		 */
		constructor: function(oSession, sHref, oFile, sDisplayName, sVersionName, sCreatorDisplayName, sComment, oCreationDate, sContentType, iContentLength, sHost, oProperties) {
			this._File = oFile;
			this.VersionName = sVersionName;
			this.CreatorDisplayName = sCreatorDisplayName || '';
			this.Comment = sComment || '';

			// Inheritance definition.
			this._super(oSession, sHref, oCreationDate, sVersionName, oCreationDate, sContentType, iContentLength, null, null, sHost, null, null, null, null, oProperties);
		},

		/**
		 * Update file to current version.
		 * @private
		 * @returns {boolean}
		 */
		UpdateToThis: function() {
			return this._File.UpdateToVersion(this);
		},

		/**
		 * Callback function to be called when version is updated on server.
		 * @callback ITHit.WebDAV.Client.Version~UpdateToThisVersionAsync
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Update file to current version.
		 * @examplecode ITHit.WebDAV.Client.Tests.Versions.ManageVersions.UpdateToThis
		 * @api
		 * @param {ITHit.WebDAV.Client.Version~UpdateToThisVersionAsync} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		UpdateToThisAsync: function(fCallback) {
			return this._File.UpdateToVersionAsync(this, fCallback);
		},

		/**
		 * Delete version by self href.
		 * @private
		 * @deprecated Use asynchronous method instead
		 */
		Delete: function() {
			var oRequest = this.Session.CreateRequest(this.__className + '.Delete()');

			// Make request.
			ITHit.WebDAV.Client.Methods.Delete.Go(oRequest, this.Href, null, this.Host);

			oRequest.MarkFinish();
		},

		/**
		 * Callback function to be called when version is deleted on server.
		 * @callback ITHit.WebDAV.Client.Version~DeleteAsyncCallback
		 * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
		 */

		/**
		 * Delete version by self href.
		 * @api
		 * @param {ITHit.WebDAV.Client.Version~DeleteAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		DeleteAsync: function(fCallback) {
			var oRequest = this.Session.CreateRequest(this.__className + '.DeleteAsync()');
			ITHit.WebDAV.Client.Methods.Delete.GoAsync(oRequest, this.Href, null, this.Host, function(oAsyncResult) {

				oRequest.MarkFinish();
				fCallback(oAsyncResult);
			});

			return oRequest;
		},

		/**
		 * Read file content. To download only a part of a file you can specify 2 parameters in ReadContent call.
		 * First parameter is the starting byte (zero-based) at witch to start content download, the second – amount
		 * of bytes to be downloaded. The library will add Range header to the request in this case.
		 * @examplecode ITHit.WebDAV.Client.Tests.Versions.ReadContent.ReadContent
		 * @api
		 * @param {number} iBytesFrom Start position to retrieve lBytesCount number of bytes from.
		 * @param {number} iBytesCount Number of bytes to retrieve.
		 * @param {ITHit.WebDAV.Client.File~ReadContentAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		ReadContentAsync: function(iBytesFrom, iBytesCount, fCallback) {
			return this._super.apply(this, arguments);
		},

		/**
		 * Writes file content.
		 * @api
		 * @param {string} sContent File content.
		 * @param {string} sLockToken Lock token.
		 * @param {string} sMimeType File mime-type.
		 * @param {ITHit.WebDAV.Client.File~WriteContentAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		WriteContentAsync: function(sContent, sLockToken, sMimeType, fCallback) {
			return this._super.apply(this, arguments);
		},

		/**
		 * Refreshes item loading data from server.
		 * @api
		 * @param {ITHit.WebDAV.Client.HierarchyItem~RefreshAsyncCallback} fCallback Function to call when operation is completed.
		 * @returns {ITHit.WebDAV.Client.Request} Request object.
		 */
		RefreshAsync: function(fCallback) {
			return this._super.apply(this, arguments);
		},

		/**
		 * @private
		 */
		GetSource: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetSourceAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetSupportedLock: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetSupportedLockAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetParent: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetParentAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		UpdateProperties: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		UpdatePropertiesAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		CopyTo: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		CopyToAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		MoveTo: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		MoveToAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		Lock: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		LockAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		RefreshLock: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		RefreshLockAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		Unlock: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		UnlockAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		SupportedFeatures: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 * @deprecated
		 */
		SupportedFeaturesAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetSupportedFeaturesAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetAllProperties: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetAllPropertiesAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetPropertyNames: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetPropertyNamesAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetPropertyValues: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetPropertyValuesAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetVersions: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		GetVersionsAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		PutUnderVersionControl: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		PutUnderVersionControlAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		UpdateToVersion: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		},

		/**
		 * @private
		 */
		UpdateToVersionAsync: function() {
			throw new ITHit.Exception('The method or operation is not implemented.');
		}

	});

})();


/**
 * @class ITHit.WebDAV.Client.Methods.Undelete
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Methods.Undelete', null, /** @lends ITHit.WebDAV.Client.Methods.Undelete.prototype */{

	__static: /** @lends ITHit.WebDAV.Client.Methods.Undelete */{

		Go: function (oRequest, sHref, sHost) {

			// Create request.
			var oWebDavRequest = ITHit.WebDAV.Client.Methods.Undelete.createRequest(oRequest, sHref, sHost);

			// Make request.
			var oResponse = oWebDavRequest.GetResponse();

			return new ITHit.WebDAV.Client.Methods.Report(oResponse);
		},

		createRequest: function (oRequest, sHref, sHost) {

			// Create request.
			var oWebDavRequest = oRequest.CreateWebDavRequest(sHost, sHref);
			oWebDavRequest.Method('UNDELETE');

			// Return request object.
			return oWebDavRequest;
		}

	}
});


/**
 * WebDavResponse class.
 * @class ITHit.WebDAV.Client.WebDavResponse
 */
ITHit.DefineClass('ITHit.WebDAV.Client.WebDavResponse', null, /** @lends ITHit.WebDAV.Client.WebDavResponse.prototype */{

	__static: /** @lends {ITHit.WebDAV.Client.WebDavResponse} */{

		ignoreXmlByMethodAndStatus: {
			'DELETE': {
				200: true
			},
			'COPY': {
				201: true,
				204: true
			},
			'MOVE': {
				201: true,
				204: true
			}
		}

	},

	/**
	 * @type {object}
	 */
	_Response: null,

	/**
	 * @type {string}
	 */
	RequestMethod: null,

	/**
	 * @type {ITHit.WebDAV.Client.HttpStatus}
	 */
	Status: null,

	/**
	 * Create new instance of WebDavResponse class.
	 * @param {object} oResponseData Response object.
	 * @param {string} sRequestMethod Request method.
	 */
	constructor: function(oResponseData, sRequestMethod) {
		this._Response     = oResponseData;
		this.RequestMethod = sRequestMethod;
		this.Status        = new ITHit.WebDAV.Client.HttpStatus(oResponseData.Status, oResponseData.StatusDescription);
	},

	/**
	 * Get response headers.
	 * @returns {object} Response headers.
	 */
	Headers: function() {
		return this._Response.Headers;
	},

	/**
	 * Get response content.
	 * @returns {string} Response XML document.
	 */
	GetResponseStream: function() {

		var oOut = null;
		if (this._Response.BodyXml
			&& !(ITHit.WebDAV.Client.WebDavResponse.ignoreXmlByMethodAndStatus[this.RequestMethod]
			&& ITHit.WebDAV.Client.WebDavResponse.ignoreXmlByMethodAndStatus[this.RequestMethod][this._Response.Status]
			)
		) {
			oOut = new ITHit.XMLDoc(this._Response.BodyXml);
		}

		return oOut;
	}

});



ITHit.DefineClass('ITHit.WebDAV.Client.Methods.ErrorResponse', null, /** @lends ITHit.WebDAV.Client.Methods.ErrorResponse.prototype */{

	ResponseDescription: '',
	Properties: null,

	/**
	 *
	 * @param oXmlDoc
	 * @param sOriginalUri
	 * @constructs
	 */
	constructor: function(oXmlDoc, sOriginalUri) {

		// Declare properties.
		this.Properties          = [];

		var oDescription = new ITHit.WebDAV.Client.PropertyName("responsedescription", ITHit.WebDAV.Client.DavConstants.NamespaceUri);

		// Create namespace resolver.
		var oResolver = new ITHit.XPath.resolver();
		oResolver.add('d', ITHit.WebDAV.Client.DavConstants.NamespaceUri);

		// Select nodes.
		var oRes = ITHit.XPath.evaluate('/d:error/*', oXmlDoc, oResolver);

		// Loop through selected nodes.
		var oNode;
		while (oNode = oRes.iterateNext()) {

			var oProp = new ITHit.WebDAV.Client.Property(oNode.cloneNode());

			if (oDescription.Equals(oProp.Name)) {
				this.ResponseDescription = oProp.StringValue();
				continue;
			}

			this.Properties.push(oProp);
		}
	}

});


/**
 * Incorrect credentials provided or insufficient permissions to access the requested item. Initializes a new instance
 * of the UnauthorizedException class with a specified error message, a reference to the inner exception that is the
 * cause of this exception, href of the item and multistatus response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.UnauthorizedException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.UnauthorizedException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.UnauthorizedException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'UnauthorizedException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oInnerException) {
		this._super(sMessage, sHref, null, ITHit.WebDAV.Client.HttpStatus.Unauthorized, oInnerException);
	}

});


/**
 * The request could not be understood by the server due to malformed syntax.
 * Initializes a new instance of the BadRequestException class with a specified error message, a reference to the
 * inner exception that is the cause of this exception, href of the item and multistatus response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.BadRequestException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.BadRequestException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.BadRequestException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'BadRequestException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.IError} [oErrorInfo] Error response containing additional error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oErrorInfo, oInnerException) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.BadRequest, oInnerException, oErrorInfo);
	}

});


/**
 * The request could not be carried because of conflict on server.
 * Initializes a new instance of the ConflictException class with a specified error message, a reference
 * to the inner exception that is the cause of this exception, href of the item and multistatus response
 * caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.ConflictException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.ConflictException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.ConflictException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'ConflictException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.IError} [oErrorInfo] Error response containing additional error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oErrorInfo, oInnerException) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.Conflict, oInnerException, oErrorInfo);
	}

});


/**
 * The item is locked. Initializes a new instance of the LockedException class with a specified error message,
 * a reference to the inner exception that is the cause of this exception, href of the item and multistatus
 * response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.LockedException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.LockedException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.LockedException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'LockedException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.IError} [oErrorInfo] Error response containing additional error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oErrorInfo, oInnerException) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.Locked, oInnerException, oErrorInfo);
	}

});


/**
 * The server refused to fulfill the request. Initializes a new instance of the ForbiddenException class with
 * a specified error message, a reference to the inner exception that is the cause of this exception, href of
 * the item and multistatus response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.ForbiddenException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.ForbiddenException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.ForbiddenException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'ForbiddenException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 * @param {ITHit.IError} [oErrorInfo] Error response containing additional error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oErrorInfo, oInnerException) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.Forbidden, oInnerException, oErrorInfo);
	}

});


/**
 * The method is not allowed. Initializes a new instance of the MethodNotAllowedException class with a specified
 * error message, a reference to the inner exception that is the cause of this exception, href of the item and
 * multistatus response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'MethodNotAllowedException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.IError} [oErrorInfo] Error response containing additional error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oErrorInfo, oInnerException) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.MethodNotAllowed, oInnerException, oErrorInfo);
	}

});


/**
 * The method is not implemented. Initializes a new instance of the NotImplementedException class with a specified
 * error message, a reference to the inner exception that is the cause of this exception, href of the item and
 * multistatus response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.NotImplementedException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.NotImplementedException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.NotImplementedException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'NotImplementedException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.IError} [oErrorInfo] Error response containing additional error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oErrorInfo, oInnerException) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.NotImplemented, oInnerException, oErrorInfo);
	}

});


/**
 * The item doesn't exist on the server. Initializes a new instance of the NotFoundException class with a specified
 * error message, a reference to the inner exception that is the cause of this exception, href of the item and
 * multistatus response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.NotFoundException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.NotFoundException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.NotFoundException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'NotFoundException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oInnerException) {
		this._super(sMessage, sHref, null, ITHit.WebDAV.Client.HttpStatus.NotFound, oInnerException);
	}

});


/**
 * Precondition failed. Initializes a new instance of the PreconditionFailedException class with a specified error
 * message, a reference to the inner exception that is the cause of this exception, href of the item and multistatus
 * response with error details.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.PreconditionFailedException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.PreconditionFailedException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.PreconditionFailedException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'PreconditionFailedException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.IError} [oErrorInfo] Error response containing additional error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oErrorInfo, oInnerException) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.PreconditionFailed, oInnerException, oErrorInfo);
	}

});


/**
 * The method could not be performed on the resource because the requested action depended on another action
 * and that action failed. Initializes a new instance of the DependencyFailedException class with a specified
 * error message, a reference to the inner exception that is the cause of this exception, href of the item
 * and multistatus response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.DependencyFailedException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.DependencyFailedException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.DependencyFailedException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'DependencyFailedException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.IError} [oErrorInfo] Error response containing additional error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oErrorInfo, oInnerException) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.DependencyFailed, oInnerException, oErrorInfo);
	}

});


/**
 * Insufficient storage exception. Initializes a new instance of the InsufficientStorageException class with
 * a specified error message, a reference to the inner exception that is the cause of this exception, href of
 * the item and error response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.InsufficientStorageException
 * @extends ITHit.WebDAV.Client.Exceptions.WebDavHttpException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.InsufficientStorageException', ITHit.WebDAV.Client.Exceptions.WebDavHttpException, /** @lends ITHit.WebDAV.Client.Exceptions.InsufficientStorageException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'InsufficientStorageException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.IError} [oErrorInfo] Error response containing additional error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oErrorInfo, oInnerException) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.InsufficientStorage, oInnerException, oErrorInfo);
	}

});


/**
 * Quota not exceeded exception. Initializes a new instance of the QuotaNotExceededException class with a
 * specified error message, a reference to the inner exception that is the cause of this exception, href of
 * the item and error response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.QuotaNotExceededException
 * @extends ITHit.WebDAV.Client.Exceptions.InsufficientStorageException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.QuotaNotExceededException', ITHit.WebDAV.Client.Exceptions.InsufficientStorageException, /** @lends ITHit.WebDAV.Client.Exceptions.QuotaNotExceededException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'QuotaNotExceededException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 * @param {ITHit.IError} [oError] Error response containing additional error information.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oInnerException, oError) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.InsufficientStorage, oInnerException, oError);
	}

});


/**
 * Sufficient disk space exception. Initializes a new instance of the SufficientDiskSpaceException class with
 * a specified error message, a reference to the inner exception that is the cause of this exception, href of
 * the item and error response caused the error.
 * @api
 * @class ITHit.WebDAV.Client.Exceptions.SufficientDiskSpaceException
 * @extends ITHit.WebDAV.Client.Exceptions.InsufficientStorageException
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.SufficientDiskSpaceException', ITHit.WebDAV.Client.Exceptions.InsufficientStorageException, /** @lends ITHit.WebDAV.Client.Exceptions.SufficientDiskSpaceException.prototype */{

	/**
	 * Exception name
	 * @type {string}
	 */
	Name: 'SufficientDiskSpaceException',

	/**
	 * @param {string} sMessage The error message string.
	 * @param {string} sHref The href of an item caused the current exception.
	 * @param {ITHit.WebDAV.Client.Multistatus} oMultistatus Multistatus response containing error information.
	 * @param {ITHit.Exception} [oInnerException] The ITHit.Exception instance that caused the current exception.
	 * @param {ITHit.IError} [oError] Error response containing additional error information.
	 */
	constructor: function(sMessage, sHref, oMultistatus, oInnerException, oError) {
		this._super(sMessage, sHref, oMultistatus, ITHit.WebDAV.Client.HttpStatus.InsufficientStorage, oInnerException, oError);
	}

});


ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.Parsers.InsufficientStorage', null, /** @lends ITHit.WebDAV.Client.Exceptions.Parsers.InsufficientStorage.prototype */{

	/**
	 * @constructs
	 * @param sMessage
	 * @param sHref
	 * @param oMultistatus
	 * @param oError
	 * @param oInnerException
	 */
	constructor: function(sMessage, sHref, oMultistatus, oError, oInnerException) {

		var sExceptionClass = 'InsufficientStorageException';

		if (1 == oError.Properties.length) {
			var oPropName = oError.Properties[0].Name;

			if (oPropName.Equals(ITHit.WebDAV.Client.DavConstants.QuotaNotExceeded)) {
				sExceptionClass = 'QuotaNotExceededException';
			} else if (oPropName.Equals(ITHit.WebDAV.Client.DavConstants.SufficientDiskSpace)) {
				sExceptionClass = 'SufficientDiskSpaceException';
			}
		}

		return new ITHit.WebDAV.Client.Exceptions[sExceptionClass]((oError.Description || sMessage), sHref, oMultistatus, oInnerException, oError);
	}

});


/**
 * Represents information about errors occurred in different elements.
 * @api
 * @class ITHit.WebDAV.Client.Error
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Error', null, /** @lends ITHit.WebDAV.Client.Error.prototype */{

    /**
     * Gets the generic description, if available.
     * @api
     * @type {string}
     */
    Description: null,

    /**
     * Array of the errors returned by server.
     * @api
     * @type {ITHit.WebDAV.Client.MultistatusResponse[]}
     */
    Responses: null

});

ITHit.DefineClass('ITHit.WebDAV.Client.Exceptions.Info.Error', ITHit.WebDAV.Client.Error, /** @lends ITHit.WebDAV.Client.Exceptions.Info.Error.prototype */{

	/**
	 * Gets the generic description, if available.
	 * @type {string}
	 */
	Description: '',

	/**
	 * Array of elements returned by server.
	 * @type {ITHit.WebDAV.Client.Property[]}
	 */
	Properties: null,

	/**
	 * Inline text, returned by server
	 * @type {string}
	 */
	BodyText: '',

	/**
	 * Represents information about errors occurred in different elements.
	 * @constructs
	 * @extends ITHit.WebDAV.Client.Error
	 */
	constructor: function(oErrorResponse) {
		this.Properties = [];

		this._super();

		// Whether error response object passed.
		if (oErrorResponse) {
			this.Description = oErrorResponse.ResponseDescription;
			this.Properties  = oErrorResponse.Properties;
		}
	}

});


ITHit.Phrases.LoadJSON(ITHit.Temp.WebDAV_Phrases);

;
(function() {

	/*
	 * Request header collection.
	 */
	var Headers = function(oHeaders) {
		this.Headers = oHeaders;
	};

	/*
	 * Save header for request.
	 * @function ITHit.WebDAV.Client.WebDavRequest.Add
	 *
	 * @param {string} sHeader Header's name.
	 * @param {string} sValue Header's value.
	 */
	Headers.prototype.Add = function(sHeader, sValue) {
		this.Headers[sHeader] = sValue;
	};

	/*
	 * Get headers dictionary as reference.
	 * @function {object} ITHit.WebDAV.Client.WebDavRequest.GetAll
	 *
	 * @returns Headers list.
	 */
	Headers.prototype.GetAll = function() {
		return this.Headers;
	};

	/**
	 * This class represents asynchronous request to WebDAV server. The instance of this class is returned from most
	 * asynchronous methods of the library. You can use it to cancel the request calling Abort() method of this class
	 * as well as to show progress attaching to Progress event.
	 * @class ITHit.WebDAV.Client.WebDavRequest
	 */
	var self = ITHit.DefineClass('ITHit.WebDAV.Client.WebDavRequest', null, /** @lends ITHit.WebDAV.Client.WebDavRequest.prototype */{

		__static: /** @lends ITHit.WebDAV.Client.WebDavRequest */{

			_IdCounter: 0,

			/**
			 * Create request.
			 * @param {string} sUri Page URI.
			 * @param {(string|Array)} mLockTokens Lock tokens for item.
			 * @param mLockTokens
			 * @param {string} [sUser]
			 * @param {string} [sPass]
			 * @param {string} [sHost]
			 * @returns {ITHit.WebDAV.Client.WebDavRequest} Request object.
			 */
			Create: function(sUri, mLockTokens, sUser, sPass, sHost) {

				// Whether host is not set than add it.
				if (/^\//.test(sUri)) {
					sUri = sHost + sUri.substr(1);
				}

				// Create WebDavRequest object for specified URI.
				var oWebDavRequest = new self(sUri, sUser, sPass);

				// If mLockTokens is string.
				if ('string' == typeof mLockTokens) {
					if (mLockTokens) {

						// Add If header.
						oWebDavRequest.Headers.Add('If', '(<'+ ITHit.WebDAV.Client.DavConstants.OpaqueLockToken + mLockTokens +'>)');
					}

					// Else if mLockTokens is an array type.
				} else if ( (mLockTokens instanceof Array) && mLockTokens.length) {

					var sLockTokensHeader = '';
					var bFirst = true;

					for (var i = 0; i < mLockTokens.length; i++) {

						// Check whether LockToken element is not null.
						ITHit.WebDAV.Client.WebDavUtil.VerifyArgumentNotNull(mLockTokens[i], "lockToken");

						// Append LockToken to header collection.
						sLockTokensHeader += (bFirst ? '' : ' ') + '(<'+ ITHit.WebDAV.Client.DavConstants.OpaqueLockToken + mLockTokens[i].LockToken +'>)';

						bFirst = false;
					}

					// Add If header.
					oWebDavRequest.Headers.Add("If", sLockTokensHeader);
				}

				return oWebDavRequest;
			},

			ProcessWebException: function(oResponseData) {

				// Get references for namespaces.
				var oResponse     = null;
				var sResponseData = '';

				if (oResponseData.BodyXml && oResponseData.BodyXml.childNodes.length) {
					oResponse     = new ITHit.XMLDoc(oResponseData.BodyXml);
					sResponseData = String(oResponse);
				}

				// Try parse multistatus response.
				var oInfo         = null,
					oErrorInfo    = null;

				if (oResponse) {
					var oErrorResponse = new ITHit.WebDAV.Client.Methods.ErrorResponse(oResponse, oResponseData.Href);
					oErrorInfo         = new ITHit.WebDAV.Client.Exceptions.Info.Error(oErrorResponse);

					var oMultiResponse = new ITHit.WebDAV.Client.Methods.MultiResponse(oResponse, oResponseData.Href);
					oInfo              = new ITHit.WebDAV.Client.Exceptions.Info.Multistatus(oMultiResponse);
				} else {
					oErrorInfo         = new ITHit.WebDAV.Client.Exceptions.Info.Error();
					oErrorInfo.BodyText = oResponseData.BodyText;
				}

				// Throw apropriate exception
				var oException = null,
					oExceptionToThrow;

				switch (oResponseData.Status) {

					case ITHit.WebDAV.Client.HttpStatus.Unauthorized.Code:
						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.UnauthorizedException(ITHit.Phrases.Exceptions.Unauthorized, oResponseData.Href, oException);
						break;

					case ITHit.WebDAV.Client.HttpStatus.Conflict.Code:
						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.ConflictException(ITHit.Phrases.Exceptions.Conflict, oResponseData.Href, oInfo, oErrorInfo, oException);
						break;

					case ITHit.WebDAV.Client.HttpStatus.Locked.Code:
						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.LockedException(ITHit.Phrases.Exceptions.Locked, oResponseData.Href, oInfo, oErrorInfo, oException);
						break;

					case ITHit.WebDAV.Client.HttpStatus.BadRequest.Code:
						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.BadRequestException(ITHit.Phrases.Exceptions.BadRequest, oResponseData.Href, oInfo, oErrorInfo, oException);
						break;

					case ITHit.WebDAV.Client.HttpStatus.Forbidden.Code:
						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.ForbiddenException(ITHit.Phrases.Exceptions.Forbidden, oResponseData.Href, oInfo, oErrorInfo, oException);
						break;

					case ITHit.WebDAV.Client.HttpStatus.MethodNotAllowed.Code:
						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException(ITHit.Phrases.Exceptions.MethodNotAllowed, oResponseData.Href, oInfo, oErrorInfo, oException);
						break;

					case ITHit.WebDAV.Client.HttpStatus.NotImplemented.Code:
						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.NotImplementedException(ITHit.Phrases.Exceptions.MethodNotAllowed, oResponseData.Href, oInfo, oErrorInfo, oException);
						break;

					case ITHit.WebDAV.Client.HttpStatus.NotFound.Code:
						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.NotFoundException(ITHit.Phrases.Exceptions.NotFound, oResponseData.Href, oException);
						break;

					case ITHit.WebDAV.Client.HttpStatus.PreconditionFailed.Code:
						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.PreconditionFailedException(ITHit.Phrases.Exceptions.PreconditionFailed, oResponseData.Href, oInfo, oErrorInfo, oException);
						break;

					case ITHit.WebDAV.Client.HttpStatus.DependencyFailed.Code:
						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.DependencyFailedException(ITHit.Phrases.Exceptions.DependencyFailed, oResponseData.Href, oInfo, oErrorInfo, oException);
						break;

					case ITHit.WebDAV.Client.HttpStatus.InsufficientStorage.Code:
						oExceptionToThrow = ITHit.WebDAV.Client.Exceptions.Parsers.InsufficientStorage(ITHit.Phrases.Exceptions.InsufficientStorage, oResponseData.Href, oInfo, oErrorInfo, oException);
						break;

					default:
						if (sResponseData) {
							sResponseData = '\n'+ ITHit.Phrases.ServerReturned +'\n----\n'+ sResponseData +'\n----\n';
						}

						oExceptionToThrow = new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(
							ITHit.Phrases.Exceptions.Http + sResponseData,
							oResponseData.Href,
							oInfo,
							new ITHit.WebDAV.Client.HttpStatus(oResponseData.Status, oResponseData.StatusDescription),
							oException,
							oErrorInfo
						);
						break;
				}

				return oExceptionToThrow;
			}

		},

		_Href: null,
		_Method: 'GET',
		_Headers: null,
		_Body: '',
		_User: null,
		_Password: null,

		Id: null,
		Headers: null,
		PreventCaching: null,
		ProgressInfo: null,
        UploadProgressInfo: null,

		/**
		 * Custom handler for get progress event
		 */
		OnProgress: null,
        OnUploadProgress: null,
		_XMLRequest: null,

		/**
		 * Create instance of WebDavRequest class.
		 * @param {string} sUri URI
		 * @param {string} [sUser]
		 * @param {string} [sPass]
		 */
		constructor: function(sUri, sUser, sPass) {
			this._Href     = sUri;
			this._Headers  = {};
			this._User     = sUser || null;
			this._Password = sPass || null;

			this.Id = self._IdCounter++;
			this.Headers   = new Headers(this._Headers);
		},

		/**
		 * Get or set method for request
		 * @param {string} sValue Method's value.
		 * @returns {string} Method's value.
		 */
		Method: function(sValue) {
			if (undefined !== sValue) {
				this._Method = sValue;
			}

			return this._Method;
		},

		Body: function(mBody) {
			if (undefined !== mBody) {
				this._Body = String(mBody);
			}

			return String(this._Body);
		},

        BodyBinary: function(mBody) {
            if (undefined !== mBody) {
                this._Body = mBody;
            }

            return this._Body;
        },

		/**
		 * Abort request. Method called native XMLRequest.Abort method.
		 */
		Abort: function() {
			if (this._XMLRequest !== null) {
				this._XMLRequest.Abort();
			}
		},

        AbortAsync: function() {
            if (this._XMLRequest !== null) {
            	var that = this;
                this._XMLRequest.OnError = function (oException) {
                    var oWebDavHttpException = new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(oException.message, sHref, null, null, oException);
                    var oAsyncResult = new ITHit.WebDAV.Client.AsyncResult(null, false, oWebDavHttpException);
                    ITHit.Events.DispatchEvent(that, 'OnFinish', [oAsyncResult, that.Id]);
                    fCallback.call(this, oAsyncResult);
                };
                this._XMLRequest.Abort();
            }
        },

		/**
		 * Make XMLHttpRequest and get response.
		 * @returns {ITHit.WebDAV.Client.WebDavResponse|null} Response object.
		 */
		GetResponse: function(fCallback) {

			// Send async request
			var bAsync = typeof fCallback === 'function';

			var sHref = this._Href;

			// Add nocache attribute for force disabled cache
			if ((ITHit.Config.PreventCaching && this.PreventCaching === null) || this.PreventCaching === true ) {
				var sAndSymbol = sHref.indexOf('?') !== -1 ? '&' : '?';
				var sNoCacheParam = sAndSymbol + 'nocache=' + new Date().getTime();

				if (sHref.indexOf('#') !== -1) {
					sHref.replace(/#/g, sNoCacheParam + '#');
				} else {
					sHref += sNoCacheParam;
				}
			}

			// Fix for XMLHttpRequest.
			// TODO: Remove fix when encoding special characters on server will be fixed.
			sHref = sHref.replace(/#/g, '%23');

			var oRequestData = new ITHit.HttpRequest(
				sHref,
				this._Method,
				this._Headers,
				this._Body
			);

			var oResponseData = ITHit.Events.DispatchEvent(this, 'OnBeforeRequestSend', oRequestData);

			if (!oResponseData || !(oResponseData instanceof ITHit.HttpResponse)) {

				// Set default user and password if specified.
				oRequestData.User     = (null === oRequestData.User) ? this._User : oRequestData.User;
				oRequestData.Password = (null === oRequestData.Password) ? this._Password : oRequestData.Password;
				oRequestData.Body = oRequestData.Body || '';

				// Send request.
				this._XMLRequest = new ITHit.XMLRequest(oRequestData, bAsync);
			}

			if (bAsync) {
				if (this._XMLRequest !== null) {
					// Call callback after receiving the response
					var that = this;
					this._XMLRequest.OnData = function (oResponseData) {
						var oWebDavResponse = null;
						var bSuccess = true;
						var oError = null;
						try {
							oWebDavResponse = that._onGetResponse(oRequestData, oResponseData);
							bSuccess = true;
						}
						catch (e) {
							oError = e;
							bSuccess = false;
						}

						var oAsyncResult = new ITHit.WebDAV.Client.CancellableResult(oWebDavResponse, bSuccess, oError, this.IsAborted);
						ITHit.Events.DispatchEvent(that, 'OnFinish', [oAsyncResult, that.Id]);
						fCallback.call(this, oAsyncResult);
					};
					this._XMLRequest.OnError = function (oException) {
						var oWebDavHttpException = new ITHit.WebDAV.Client.Exceptions.WebDavHttpException(oException.message, sHref, null, null, oException);
						var oAsyncResult = new ITHit.WebDAV.Client.AsyncResult(null, false, oWebDavHttpException, this.IsAborted);
						ITHit.Events.DispatchEvent(that, 'OnFinish', [oAsyncResult, that.Id]);
						fCallback.call(this, oAsyncResult);
					};
					this._XMLRequest.OnProgress = function (oEvent) {
						// IE8 has not arguments in onprogress event
						if (!oEvent) {
							return;
						}

						that.ProgressInfo = oEvent;
						ITHit.Events.DispatchEvent(that, 'OnProgress', [oEvent, that.Id]);

						if (typeof that.OnProgress === 'function') {
							that.OnProgress(oEvent);
						}
					};

                    this._XMLRequest.OnUploadProgress = function (oEvent) {
                        // IE8 has not arguments in onprogress event
                        if (!oEvent) {
                            return;
                        }

                        that.UploadProgressInfo = oEvent;
                        ITHit.Events.DispatchEvent(that, 'OnUploadProgress', [oEvent, that.Id]);

                        if (typeof that.OnUploadProgress === 'function') {
                            that.OnUploadProgress(oEvent);
                        }
                    };

					this._XMLRequest.Send();
				} else {
					// Only call callback
					var oWebDavResponse = this._onGetResponse(oRequestData, oResponseData);
					fCallback.call(this, oWebDavResponse);
				}
			} else {
				if (this._XMLRequest !== null) {
					this._XMLRequest.Send();
					oResponseData = this._XMLRequest.GetResponse();
				}

				// Send response synchronous
				return this._onGetResponse(oRequestData, oResponseData);
			}
		},

	    /**
         *
         * @return {ITHit.WebDAV.Client.WebDavResponse}
         */
		_onGetResponse: function(oRequestData, oResponseData) {

			oResponseData.RequestMethod = this._Method;
			ITHit.Events.DispatchEvent(this, 'OnResponse', [oResponseData, this.Id]);

			var oStatus = new ITHit.WebDAV.Client.HttpStatus(oResponseData.Status, oResponseData.StatusDescription);

			// If status is 278 treat this as a redirect, 302 redirect is processed automatically, no way to display login page
			// http://stackoverflow.com/questions/199099/how-to-manage-a-redirect-request-after-a-jquery-ajax-call
			if (oResponseData.Status == ITHit.WebDAV.Client.HttpStatus.Redirect.Code) {
				window.location.replace(oResponseData.Headers['Location']);
			}

			// If status is not success then raise exception.
			if (!oStatus.IsSuccess()) {
				throw self.ProcessWebException(oResponseData);
			}

			// Return response.
			return new ITHit.WebDAV.Client.WebDavResponse(oResponseData, oRequestData.Method);
		}

	});

})();


;
(function() {

	/**
	 * Represents a context for one or many requests.
	 * @api
	 * @class ITHit.WebDAV.Client.RequestProgress
	 */
	var self = ITHit.DefineClass('ITHit.WebDAV.Client.RequestProgress', null, /** @lends ITHit.WebDAV.Client.RequestProgress.prototype */{

		/**
		 * Progress in percents
		 * @api
		 * @type {number}
		 */
		Percent: 0,

		/**
		 * Count of complete operations
		 * @api
		 * @type {number}
		 */
		CountComplete: 0,

		/**
		 * Total operations count
		 * @api
		 * @type {number}
		 */
		CountTotal: 0,

		/**
		 * Count of loaded bytes
		 * @api
		 * @type {number}
		 */
		BytesLoaded: 0,

		/**
		 * Total bytes. This param can be changed in progress, if request has many operations (sub-requests).
		 * @api
		 * @type {number}
		 */
		BytesTotal: 0,

		/**
		 * Flag indicating if the resource concerned by the XMLHttpRequest ProgressEvent has a length that can be calculated.
		 * @api
		 * @type {boolean}
		 */
		LengthComputable: true,

		/**
		 * @type {object}
		 */
		_RequestsComplete: null,

		/**
		 * @type {object}
		 */
		_RequestsXhr: null,

		/**
		 *
		 * @param {number} [iRequestsCount] Requests count
		 */
		constructor: function(iRequestsCount) {
			this.CountTotal = iRequestsCount;
			this._RequestsComplete = {};
			this._RequestsXhr = {};
		},

		/**
		 * @param {number} iRequestId
		 */
		SetComplete: function(iRequestId) {
			if (this._RequestsComplete[iRequestId]) {
				return;
			}

			this._RequestsComplete[iRequestId] = true;
			this.CountComplete++;

			if (this._RequestsXhr[iRequestId]) {
				this._RequestsXhr[iRequestId].loaded = this._RequestsXhr[iRequestId].total;
				this.SetXhrEvent(iRequestId, this._RequestsXhr[iRequestId]);
			} else {
				this._UpdatePercent();
			}
		},

		/**
		 * @param {number} iRequestId
		 * @param {XMLHttpRequestProgressEvent} oXhrEvent
		 */
		SetXhrEvent: function(iRequestId, oXhrEvent) {
			this._RequestsXhr[iRequestId] = oXhrEvent;

			if (this.LengthComputable === false) {
				return;
			}

			this._ResetBytes();

			for (var iId in this._RequestsXhr) {
				if (!this._RequestsXhr.hasOwnProperty(iId)) {
					continue;
				}

				var oProgress = this._RequestsXhr[iId];
				if (oProgress.lengthComputable === false || !oProgress.total) {
					this.LengthComputable = false;
					this._ResetBytes();
					break;
				}

				this.BytesLoaded += oProgress.loaded;
				this.BytesTotal += oProgress.total;
			}

			this._UpdatePercent();
		},

		_ResetBytes: function() {
			this.BytesLoaded = 0;
			this.BytesTotal = 0;
		},

		_UpdatePercent: function() {
			if (this.LengthComputable) {
				this.Percent = 0;
				for (var iId in this._RequestsXhr) {
					if (!this._RequestsXhr.hasOwnProperty(iId)) {
						continue;
					}

					var oProgress = this._RequestsXhr[iId];
					this.Percent += (oProgress.loaded * 100 / oProgress.total) / this.CountTotal;
				}
			} else {
				this.Percent = this.CountComplete * 100 / this.CountTotal;
			}

			this.Percent = Math.round(this.Percent * 100) / 100;
		}

	});

})();


;
(function() {

	/**
	 * Represents a context for one or many requests.
	 * @api
	 * @fires ITHit.WebDAV.Client.Request#OnProgress
	 * @fires ITHit.WebDAV.Client.Request#OnError
	 * @fires ITHit.WebDAV.Client.Request#OnFinish
	 * @class ITHit.WebDAV.Client.Request
	 */
	var self = ITHit.DefineClass('ITHit.WebDAV.Client.Request', null, /** @lends ITHit.WebDAV.Client.Request.prototype */{

		__static: /** @lends ITHit.WebDAV.Client.Request */{

			/**
			 * Progress event trigger on update information about request progress.
			 * See {@link ITHit.WebDAV.Client.RequestProgress} for more information.
			 * @api
			 * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.Progress.Progress
			 * @event ITHit.WebDAV.Client.Request#OnProgress
			 * @property {ITHit.WebDAV.Client.RequestProgress} Progress Progress info instance
			 * @property {ITHit.WebDAV.Client.Request} Request Current request
			 */
			EVENT_ON_PROGRESS: 'OnProgress',

            /**
             * Progress event trigger on update information about request progress.
             * See {@link ITHit.WebDAV.Client.RequestProgress} for more information.
             * @event ITHit.WebDAV.Client.Request#OnUploadProgress
             * @property {ITHit.WebDAV.Client.RequestProgress} Progress Progress info instance
             * @property {ITHit.WebDAV.Client.Request} Request Current request
             */
            EVENT_ON_UPLOAD_PROGRESS: 'OnUploadProgress',

			/**
			 * Error event trigger when one of request operations have error.
			 * Notice: This event trigger before async method callback.
			 * @api
			 * @event ITHit.WebDAV.Client.Request#OnError
			 * @property {Error|ITHit.WebDAV.Client.Exceptions.WebDavException} Error Error object
			 * @property {ITHit.WebDAV.Client.Request} Request Current request
			 */
			EVENT_ON_ERROR: 'OnError',

			/**
			 * Finish event trigger once when all operations in requests is complete.
			 * Notice: This event trigger before async method callback.
			 * @api
			 * @event ITHit.WebDAV.Client.Request#OnFinish
			 * @property {ITHit.WebDAV.Client.Request} Request Current request
			 */
			EVENT_ON_FINISH: 'OnFinish',

            EVENT_ON_ABORT: 'OnAbort',

			IdCounter: 0

		},

		/**
		 * Auto generated unique request id
		 * @type {number}
		 */
		Id: null,

		/**
		 * Current WebDAV session.
		 * @type {ITHit.WebDAV.Client.WebDavSession}
		 */
		Session: null,

		/**
		 * Context name
		 * @type {string}
		 */
		Name: null,

		/**
		 * Progress info object, auto updated on `OnProgress` event.
		 * @api
		 * @type {ITHit.WebDAV.Client.RequestProgress}
		 */
		Progress: null,

        /**
         * Progress info object, auto updated on `OnUploadProgress` event.
         * @public
         * @type {ITHit.WebDAV.Client.RequestProgress}
         */
        UploadProgress: null,

		/**
		 * Count of requests
		 * @type {number}
		 */
		_RequestsCount: null,

		/**
		 * @type {ITHit.WebDAV.Client.WebDavRequest[]}
		 */
		_WebDavRequests: null,

		/**
		 * @type {boolean}
		 */
		_IsFinish: false,

		/**
		 *
		 * @param {ITHit.WebDAV.Client.WebDavSession} oSession Current WebDAV session.
		 * @param {string} [sName] Context name
		 * @param {number} [iRequestsCount] Requests count
		 */
		constructor: function(oSession, sName, iRequestsCount) {
			sName = sName || this.__instanceName;
			iRequestsCount = iRequestsCount || 1;

			this.Session = oSession;
			this.Name = sName;

			this.Id = self.IdCounter++;
			this._WebDavRequests = [];
			this._WebDavResponses = {};
			this._RequestsCount = iRequestsCount;
			this.Progress = new ITHit.WebDAV.Client.RequestProgress(iRequestsCount);
            this.UploadProgress = new ITHit.WebDAV.Client.RequestProgress(iRequestsCount);
		},

		/**
		 * @api
		 * @param {string} sEventName
		 * @param fCallback
		 * @param {object} [oContext]
		 */
		AddListener: function(sEventName, fCallback, oContext) {
			oContext = oContext || null;

			switch (sEventName) {
				case self.EVENT_ON_PROGRESS:
                case self.EVENT_ON_UPLOAD_PROGRESS:
				case self.EVENT_ON_ERROR:
				case self.EVENT_ON_FINISH:
					ITHit.Events.AddListener(this, sEventName, fCallback, oContext);
					break;

				default:
					throw new ITHit.WebDAV.Client.Exceptions.WebDavException('Not found event name `' + sEventName + '`');
			}
		},

		/**
		 * @api
		 * @param {string} sEventName
		 * @param fCallback
		 * @param {object} [oContext]
		 */
		RemoveListener: function(sEventName, fCallback, oContext) {
			oContext = oContext || null;

			switch (sEventName) {
				case self.EVENT_ON_PROGRESS:
				case self.EVENT_ON_UPLOAD_PROGRESS:
				case self.EVENT_ON_ERROR:
				case self.EVENT_ON_FINISH:
					ITHit.Events.RemoveListener(this, sEventName, fCallback, oContext);
					break;

				default:
					throw new ITHit.WebDAV.Client.Exceptions.WebDavException('Not found event name `' + sEventName + '`');
			}
		},

		/**
		 * Cancels asynchronous request. The Finish event and the callback function will be called immediately after this method call.
		 * @api
		 */
		Abort: function() {
			for (var i = 0, l = this._WebDavRequests.length; i < l; i++) {
				this._WebDavRequests[i].Abort();
			}

			// @todo stop new requests, call finish?
		},

        /**
         * Cancels asynchronous request. The Finish event and the callback function will not be called after this method call.
         * @public
         */
        AbortAsync: function(fCallback, thisArg) {

            var fAbortListener = function(oRequest){
                ITHit.Events.RemoveListener(this, self.EVENT_ON_ABORT, fAbortListener);
                fCallback.call(thisArg, oRequest);
            };
            ITHit.Events.AddListener(this, self.EVENT_ON_ABORT, fAbortListener);

            for (var i = 0, l = this._WebDavRequests.length; i < l; i++) {
                this._WebDavRequests[i].Abort();
            }
        },

		MarkFinish: function() {
			if (this._IsFinish === true) {
				return;
			}
			this._IsFinish = true;

			ITHit.Events.DispatchEvent(this, self.EVENT_ON_FINISH, [{Request: this}]);

			var oDateNow = new Date();
			ITHit.Logger.WriteMessage('[' + this.Id + '] ----------------- Finished: ' + oDateNow.toUTCString() + ' [' + oDateNow.getTime() + '] -----------------' + '\n', ITHit.LogLevel.Info);

			// Remove listeners
			/*ITHit.Events.RemoveAllListeners(this, self.EVENT_ON_PROGRESS);
			ITHit.Events.RemoveAllListeners(this, self.EVENT_ON_ERROR);
			ITHit.Events.RemoveAllListeners(this, self.EVENT_ON_FINISH);*/
		},

        MarkAbort: function() {
            if (this._IsFinish === true) {
                return;
            }
            this._IsFinish = true;

            ITHit.Events.DispatchEvent(this, self.EVENT_ON_ABORT, [{Request: this}]);

            var oDateNow = new Date();
            ITHit.Logger.WriteMessage('[' + this.Id + '] ----------------- Aborted: ' + oDateNow.toUTCString() + ' [' + oDateNow.getTime() + '] -----------------' + '\n', ITHit.LogLevel.Info);

            // Remove listeners
            /*ITHit.Events.RemoveAllListeners(this, self.EVENT_ON_PROGRESS);
            ITHit.Events.RemoveAllListeners(this, self.EVENT_ON_ERROR);
            ITHit.Events.RemoveAllListeners(this, self.EVENT_ON_FINISH);*/
        },

		/**
		 * Create request.
		 * @param {string} sHost
		 * @param {string} sPath Item path.
		 * @param {(string|ITHit.WebDAV.Client.LockUriTokenPair)} [mLockTokens] Lock token for item.
		 * @returns {ITHit.WebDAV.Client.WebDavRequest} Request object.
		 */
		CreateWebDavRequest: function(sHost, sPath, mLockTokens) {
			var sId = this.Id;
			var oDateNow = new Date();

			// Check count requests
			if (this._WebDavRequests.length >= this._RequestsCount && typeof window.console !== 'undefined') {
				console.error('Wrong count of requests in [' + this.Id + '] `' + this.Name + '`');
			}

			ITHit.Logger.WriteMessage('\n[' + sId + '] ----------------- Started: ' + oDateNow.toUTCString() + ' [' + oDateNow.getTime() + '] -----------------', ITHit.LogLevel.Info);
			ITHit.Logger.WriteMessage('[' + sId + '] Context Name: ' + this.Name, ITHit.LogLevel.Info);

			var oWebDavRequest = this.Session.CreateWebDavRequest(sHost, sPath, mLockTokens);

			// Add listeners for write logs
			ITHit.Events.AddListener(oWebDavRequest, 'OnBeforeRequestSend', '_OnBeforeRequestSend', this);
			ITHit.Events.AddListener(oWebDavRequest, 'OnResponse', '_OnResponse', this);

			// Only for async requests
			ITHit.Events.AddListener(oWebDavRequest, 'OnProgress', '_OnProgress', this);
            ITHit.Events.AddListener(oWebDavRequest, 'OnUploadProgress', '_OnUploadProgress', this);
			ITHit.Events.AddListener(oWebDavRequest, 'OnFinish', '_OnFinish', this);

			this._WebDavRequests.push(oWebDavRequest);
			return oWebDavRequest;
		},

		GetInternalRequests: function() {
			var aInternalRequests = [];
			for (var i = 0, l = this._WebDavRequests.length; i < l; i++) {
				aInternalRequests.push({
					Request: this._WebDavRequests[i],
					Response: this._WebDavResponses[this._WebDavRequests[i].Id] || null,
				});
			}
			return aInternalRequests;
		},

		_OnBeforeRequestSend: function(oRequestData) {
			this._WriteRequestLog(oRequestData);
		},

		_OnResponse: function(oResponseData, iRequestId) {
			this._WebDavResponses[iRequestId] = oResponseData;
			this._WriteResponseLog(oResponseData);
		},

		_OnProgress: function(oEvent, iRequestId) {
			var iPreviousProgressPercent = this.Progress.Percent;
			this.Progress.SetXhrEvent(iRequestId, oEvent);

			if (this.Progress.Percent !== iPreviousProgressPercent) {
				ITHit.Events.DispatchEvent(this, self.EVENT_ON_PROGRESS, [{Progress: this.Progress, Request: this}]);
			}
		},

        _OnUploadProgress: function(oEvent, iRequestId) {
            var iPreviousProgressPercent = this.UploadProgress.Percent;
            this.UploadProgress.SetXhrEvent(iRequestId, oEvent);

            if (this.UploadProgress.Percent !== iPreviousProgressPercent) {
                ITHit.Events.DispatchEvent(this, self.EVENT_ON_UPLOAD_PROGRESS, [{Progress: this.UploadProgress, Request: this}]);
            }
        },

		_OnFinish: function(oAsyncResult, iRequestId) {
			var iPreviousProgressPercent = this.Progress.Percent;
            var iPreviousUploadProgressPercent = this.UploadProgress.Percent;

			// Force set progress as 100%
			this.Progress.SetComplete(iRequestId);
			if (this.Progress.Percent !== iPreviousProgressPercent) {
				ITHit.Events.DispatchEvent(this, self.EVENT_ON_PROGRESS, [{Progress: this.Progress, Request: this}]);
			}

            this.UploadProgress.SetComplete(iRequestId);
            if (this.UploadProgress.Percent !== iPreviousUploadProgressPercent) {
                ITHit.Events.DispatchEvent(this, self.EVENT_ON_UPLOAD_PROGRESS, [{Progress: this.UploadProgress, Request: this}]);
            }

			if (!oAsyncResult.IsSuccess) {
				ITHit.Events.DispatchEvent(this, self.EVENT_ON_ERROR, [{Error: oAsyncResult.Error, AsyncResult: oAsyncResult, Request: this}]);
			}
		},

		_WriteRequestLog: function(oRequestData) {
			// Log request method and URI.
			ITHit.Logger.WriteMessage('[' + this.Id + '] ' + oRequestData.Method + ' ' + oRequestData.Href, ITHit.LogLevel.Info);

			// Log request headers.
			var aHeaders = [];
			for (var sHeader in oRequestData.Headers) {
				if (oRequestData.Headers.hasOwnProperty(sHeader)) {
					aHeaders.push(sHeader + ': ' + oRequestData.Headers[sHeader]);
				}
			}
			ITHit.Logger.WriteMessage('[' + this.Id + '] ' + aHeaders.join('\n'), ITHit.LogLevel.Info);

			var sBody = String(oRequestData.Body) || '';

			// Log request body if method is not PUT and body is not empty.
			if (oRequestData.Method.toUpperCase() !== 'PUT' && oRequestData.Body) {
				ITHit.Logger.WriteMessage('[' + this.Id + '] ' + sBody, ITHit.LogLevel.Info);
			}
		},

		_WriteResponseLog: function(oResponseData) {
			// Log response status
			ITHit.Logger.WriteMessage('\n[' + this.Id + '] '+ oResponseData.Status +' '+ oResponseData.StatusDescription, ITHit.LogLevel.Info);

			// Log response headers.
			var aHeaders = [];
			for (var sHeader in oResponseData.Headers) {
				if (oResponseData.Headers.hasOwnProperty(sHeader)) {
					aHeaders.push(sHeader + ': ' + oResponseData.Headers[sHeader]);
				}
			}
			ITHit.Logger.WriteMessage('[' + this.Id + '] ' + aHeaders.join('\n'), ITHit.LogLevel.Info);

			// Log error message.
			var bIsSuccess = (parseInt(oResponseData.Status / 100) == 2);
			var sResponseData = oResponseData.BodyXml && oResponseData.BodyXml.childNodes.length ?
				String(new ITHit.XMLDoc(oResponseData.BodyXml)) :
				oResponseData.BodyText;

			if (!bIsSuccess || oResponseData.RequestMethod.toUpperCase() !== "GET") {
				ITHit.Logger.WriteMessage('[' + this.Id + '] ' + sResponseData, bIsSuccess ? ITHit.LogLevel.Info : ITHit.LogLevel.Debug);
			}
		}

	});

})();


;
(function() {

    var self = ITHit.DefineClass('ITHit.WebDAV.Client.WebDavSession', null, /** @lends ITHit.WebDAV.Client.WebDavSession.prototype */{

        __static: /** @lends ITHit.WebDAV.Client.WebDavSession */{

            /**
             * Version of AJAX Library
             * @api
             */
            Version: '5.20.5641.0',

            /**
            * Protocol Version of AJAX Library
            * @api
            */
            ProtocolVersion: /(\d+)(?!.*\d)/.exec(ITHit.WebDAV.Client.DavConstants.ProtocolName)[0],

            /**
             * The OnBeforeRequestSend event is fired before request is being submitted to server and provides all
             * information that is used when creating the request such as URL, HTTP verb, headers and request body.
             * @api
             * @examplecode ITHit.WebDAV.Client.Tests.WebDavSession.Events.BeforeRequestSend
             * @event ITHit.WebDAV.Client.WebDavSession#OnBeforeRequestSend
             * @property {string} Method Request method
             * @property {string} Href Request absolute path
             * @property {object} Headers Key-value object with headers
             * @property {string} Body Request Body
             */
            EVENT_ON_BEFORE_REQUEST_SEND: 'OnBeforeRequestSend',

            /**
             * The OnResponse event fires when the data is received from server. In your event handler you can update
             * any data received from server.
             * @api
             * @examplecode ITHit.WebDAV.Client.Tests.WebDavSession.Events.Response
             * @event ITHit.WebDAV.Client.WebDavSession#OnResponse
             * @property {number} Status Response status code
             * @property {string} StatusDescription Response status description
             * @property {object} Headers Key-value object with headers
             * @property {string} Body Response Body
             */
            EVENT_ON_RESPONSE: 'OnResponse'

        },

        ServerEngine: null,
        _IsIisDetected: null,
        _User: '',
        _Pass: '',

        /**
         * @classdesc Session for accessing WebDAV servers.
         * @example
         *  &lt;!DOCTYPE html&gt;
         *  &lt;html lang="en"&gt;
         *  &lt;head&gt;
         *      &lt;title&gt;IT Hit WebDAV Ajax Library&lt;/title&gt;
         *      &lt;script src="http://www.ajaxbrowser.com/ITHitService/WebDAVAJAXLibrary/ITHitWebDAVClient.js" type="text/javascript"&gt;&lt;/script&gt;
         *      &lt;script type="text/javascript"&gt;
         *          var sFolderUrl = 'http://localhost:35829/';
         *          var oSession = new ITHit.WebDAV.Client.WebDavSession();
         *
         *          oSession.OpenFolderAsync(sFolderUrl, null, function (oFolderAsyncResult) {
         *              if (!oFolderAsyncResult.IsSuccess) {
         *                  console.error(oFolderAsyncResult.Error);
         *                  return;
         *               }
         *
         *              /&#42;&#42; &#64;typedef {ITHit.WebDAV.Client.Folder} oFolder &#42;/
         *              var oFolder = oFolderAsyncResult.Result;
         *
         *              console.log(oFolder.Href);
         *
         *              oFolder.GetChildrenAsync(false, null, function (oAsyncResult) {
         *                  if (!oAsyncResult.IsSuccess) {
         *                      console.error(oFolderAsyncResult.Error);
         *                      return;
         *                  }
         *
         *                  /&#42;&#42; &#64;typedef {ITHit.WebDAV.Client.HierarchyItem[]} aHierarchyItems &#42;/
         *                  var aHierarchyItems = oAsyncResult.Result;
         *
         *                  for (var i = 0, l = aHierarchyItems.length; i &lt; l; i++) {
         *                      var sSize = aHierarchyItems[i].ResourceType !== ITHit.WebDAV.Client.ResourceType.Folder ?
         *                          Math.round(aHierarchyItems[i].ContentLength / 1000) + ' Kb' :
         *                          null;
         *                      console.log(' [' + aHierarchyItems[i].ResourceType + '] ' + aHierarchyItems[i].DisplayName + (sSize ? ', ' + sSize : ''));
         *                  }
         *              });
         *          });
         *      &lt;/script&gt;
         *  &lt;/head&gt;
         *  &lt;body&gt;
         *  &lt;/body&gt;
         *  &lt;/html&gt;
         * @api
         * @fires ITHit.WebDAV.Client.WebDavSession#OnBeforeRequestSend
         * @fires ITHit.WebDAV.Client.WebDavSession#OnResponse
         * @constructs
         */
        constructor: function() {
        },

        /**
         * @api
         * @param {string} sEventName
         * @param fCallback
         * @param {object} [oContext]
         */
        AddListener: function(sEventName, fCallback, oContext) {
            oContext = oContext || null;

            switch (sEventName) {
                case self.EVENT_ON_BEFORE_REQUEST_SEND:
                case self.EVENT_ON_RESPONSE:
                    ITHit.Events.AddListener(this, sEventName, fCallback, oContext);
                    break;

                default:
                    throw new ITHit.WebDAV.Client.Exceptions.WebDavException('Not found event name `' + sEventName + '`');
            }
        },

        /**
         * @api
         * @param {string} sEventName
         * @param fCallback
         * @param {object} [oContext]
         */
        RemoveListener: function(sEventName, fCallback, oContext) {
            oContext = oContext || null;

            switch (sEventName) {
                case self.EVENT_ON_BEFORE_REQUEST_SEND:
                case self.EVENT_ON_RESPONSE:
                    ITHit.Events.RemoveListener(this, sEventName, fCallback, oContext);
                    break;

                default:
                    throw new ITHit.WebDAV.Client.Exceptions.WebDavException('Not found event name `' + sEventName + '`');
            }
        },

        /**
         * Load File object corresponding to path.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {string} sPath Path to the file.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. Default is empty array.
         * @returns {ITHit.WebDAV.Client.File} File corresponding to requested path.
         * @throws ITHit.WebDAV.Client.Exceptions.UnauthorizedException Incorrect credentials provided or insufficient permissions to access the requested item.
         * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException The requested file doesn't exist on the server.
         * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException The server refused to fulfill the request.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
         */
        OpenFile: function(sPath, aProperties) {
			aProperties = aProperties || [];

            var oRequest = this.CreateRequest(this.__className + '.OpenFile()');
            var oFile = ITHit.WebDAV.Client.File.OpenItem(oRequest, sPath, aProperties);

            oRequest.MarkFinish();
            return oFile;
        },

        /**
         * Callback function to be called when file loaded from server.
         * @callback ITHit.WebDAV.Client.WebDavSession~OpenFileAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.File} oResult.Result File corresponding to requested path.
         */

        /**
         * Load File object corresponding to path.
         * @api
         * @param {string} sPath Path to the file.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. Default is empty array.
         * @param {ITHit.WebDAV.Client.WebDavSession~OpenFileAsyncCallback} fCallback Function to call when operation is completed.
         * @returns {ITHit.WebDAV.Client.Request} Request object.
         */
        OpenFileAsync: function(sPath, aProperties, fCallback) {
			aProperties = aProperties || [];

			var oRequest = this.CreateRequest(this.__className + '.OpenFileAsync()');
            ITHit.WebDAV.Client.File.OpenItemAsync(oRequest, sPath, aProperties, function(oAsyncResult) {

                oRequest.MarkFinish();
                fCallback(oAsyncResult);
            });

            return oRequest;
        },

        /**
         * Legacy proxy to OpenFile() method
         * @private
         * @deprecated
         * @param sPath
         * @param [aProperties]
         */
        OpenResource: function(sPath, aProperties) {
			aProperties = aProperties || [];

			return this.OpenFile(sPath, aProperties);
        },

        /**
         * Legacy proxy to OpenFileAsync() method
         * @private
         * @deprecated
         * @param sPath
         * @param aProperties
         * @param fCallback
         */
        OpenResourceAsync: function(sPath, aProperties, fCallback) {
			aProperties = aProperties || [];

			return this.OpenFileAsync(sPath, aProperties, fCallback);
        },

        /**
         * Returns Folder object corresponding to path.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {string} sPath Path to the folder.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. Default is empty array.
         * @returns {ITHit.WebDAV.Client.Folder} Folder corresponding to requested path.
         * @throws ITHit.WebDAV.Client.Exceptions.UnauthorizedException Incorrect credentials provided or insufficient permissions to access the requested item.
         * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException The requested folder doesn't exist on the server.
         * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException The server refused to fulfill the request.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
         */
        OpenFolder: function(sPath, aProperties) {
			aProperties = aProperties || [];

			var oRequest = this.CreateRequest(this.__className + '.OpenFolder()');
            var oFolder = ITHit.WebDAV.Client.Folder.OpenItem(oRequest, sPath, aProperties);

            oRequest.MarkFinish();
            return oFolder;
        },

        /**
         * Callback function to be called when folder loaded from server.
         * @callback ITHit.WebDAV.Client.WebDavSession~OpenFolderAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.Folder} oResult.Result Folder corresponding to requested path.
         */

        /**
         * Returns Folder object corresponding to path.
         * @examplecode ITHit.WebDAV.Client.Tests.HierarchyItems.GetItemBySession.GetFolder
         * @api
         * @param {string} sPath Path to the folder.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. Default is empty array.
         * @param {ITHit.WebDAV.Client.WebDavSession~OpenFolderAsyncCallback} fCallback Function to call when operation is completed.
         */
        OpenFolderAsync: function(sPath, aProperties, fCallback) {
			aProperties = aProperties || [];

			var oRequest = this.CreateRequest(this.__className + '.OpenFolderAsync()');
            ITHit.WebDAV.Client.Folder.OpenItemAsync(oRequest, sPath, aProperties, function(oAsyncResult) {

                oRequest.MarkFinish();
                fCallback(oAsyncResult);
            });

            return oRequest;
        },

        /**
         * Returns HierarchyItem object corresponding to path.
         * @private
         * @deprecated Use asynchronous method instead
         * @param {string} sPath Path to the item.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} [aProperties] Additional properties requested from server. Default is empty array.
         * @returns {ITHit.WebDAV.Client.HierarchyItem} Item corresponding to requested path.
         * @throws ITHit.WebDAV.Client.Exceptions.UnauthorizedException Incorrect credentials provided or insufficient permissions to access the requested item.
         * @throws ITHit.WebDAV.Client.Exceptions.NotFoundException The requested folder doesn't exist on the server.
         * @throws ITHit.WebDAV.Client.Exceptions.ForbiddenException The server refused to fulfill the request.
         * @throws ITHit.WebDAV.Client.Exceptions.WebDavException Unexpected error occurred.
         */
        OpenItem: function(sPath, aProperties) {
			aProperties = aProperties || [];

			var oRequest = this.CreateRequest(this.__className + '.OpenItem()');
            var oItem = ITHit.WebDAV.Client.HierarchyItem.OpenItem(oRequest, sPath, aProperties);

            oRequest.MarkFinish();
            return oItem;
        },

        /**
         * Callback function to be called when items loaded from server.
         * @callback ITHit.WebDAV.Client.WebDavSession~OpenItemAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.HierarchyItem} oResult.Result Item corresponding to requested path.
         */

        /**
         * Returns HierarchyItem object corresponding to path.
         * @api
         * @param {string} sPath Path to the resource.
		 * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. Default is empty array.
         * @param {ITHit.WebDAV.Client.WebDavSession~OpenItemAsyncCallback} fCallback Function to call when operation is completed.
         */
        OpenItemAsync: function(sPath, aProperties, fCallback) {
			aProperties = aProperties || [];

            var oRequest = this.CreateRequest(this.__className + '.OpenItemAsync()');
            ITHit.WebDAV.Client.HierarchyItem.OpenItemAsync(oRequest, sPath, aProperties, function(oAsyncResult) {

                oRequest.MarkFinish();
                fCallback(oAsyncResult);
            });

            return oRequest;
        },

        /**
         * Callback function to be called when folder creates on server.
         * @callback ITHit.WebDAV.Client.WebDavSession~CreateFolderAsyncCallback
         * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
         * @param {ITHit.WebDAV.Client.HierarchyItem} oResult.Result Item corresponding to requested path.
         */

        /**
         * Creates folder corresponding to path.
         * @api
         * @param {string} sPath Path to the resource.
         * @param {ITHit.WebDAV.Client.PropertyName[]} aProperties Additional properties requested from server. Default is empty array.
         * @param {ITHit.WebDAV.Client.WebDavSession~CreateFolderAsyncCallback} fCallback Function to call when operation is completed.
         */
        CreateFolderAsync: function(sPath, aProperties, fCallback) {
            aProperties = aProperties || [];
            var oRequest = this.CreateRequest(this.__className + '.CreateFolderAsync()');
            var sHref = ITHit.WebDAV.Client.Encoder.Encode(sPath);
            var sHost = ITHit.WebDAV.Client.HierarchyItem.GetHost(sHref);
            ITHit.WebDAV.Client.Methods.Mkcol.GoAsync(oRequest, sHref, aProperties, sHost, function(oAsyncResult) {
                oRequest.MarkFinish();
                fCallback(oAsyncResult);
            });

            return oRequest;
        },

        /**
         * Create request context.
         * @param {string} [sName]
         * @param {number} [iRequestsCount]
         * @returns {ITHit.WebDAV.Client.Request} Request context.
         */
        CreateRequest: function(sName, iRequestsCount){
            return new ITHit.WebDAV.Client.Request(this, sName, iRequestsCount);
        },

        /**
         * Create request.
         * @param {string} sHost
         * @param {string} sPath Item path.
         * @param {(string|ITHit.WebDAV.Client.LockUriTokenPair)} [mLockTokens] Lock token for item.
         * @returns {ITHit.WebDAV.Client.WebDavRequest} Request object.
         */
        CreateWebDavRequest: function(sHost, sPath, mLockTokens){

            if ('undefined' == typeof mLockTokens) {
                mLockTokens = [];
            }

            // Return new WebDavRequest object.
            var oWebDavRequest = ITHit.WebDAV.Client.WebDavRequest.Create(sPath, mLockTokens, this._User, this._Pass, sHost);

            // Attach event listener.
            ITHit.Events.AddListener(oWebDavRequest, 'OnBeforeRequestSend', 'OnBeforeRequestSendHandler', this);
            ITHit.Events.AddListener(oWebDavRequest, 'OnResponse', 'OnResponseHandler', this);

            return oWebDavRequest;
        },

        OnBeforeRequestSendHandler: function(oRequestData, oWebDavRequest) {

            ITHit.Events.RemoveListener(oWebDavRequest, 'OnBeforeRequestSend', 'OnBeforeRequestSendHandler', this);
            return ITHit.Events.DispatchEvent(this, 'OnBeforeRequestSend', oRequestData);
        },

        OnResponseHandler: function(oResponseData, oWebDavRequest) {

            var oWebDavRequest = arguments[arguments.length-1];

            // set version
            if (this.ServerEngine === null) {
                // Get webdav server version
                this.ServerEngine = oResponseData.GetResponseHeader('x-engine', true);
            }
            if (this._IsIisDetected === null) {
                // check Server header to match the IIS server
                var sServerHeader = oResponseData.GetResponseHeader('server', true);
                this._IsIisDetected = (/*/^Microsoft-HTTPAPI\//i.test(sServerHeader) ||*/ /^Microsoft-IIS\//i.test(sServerHeader));
            }

            ITHit.Events.RemoveListener(oWebDavRequest, 'OnResponse', 'OnResponseHandler', this);
            return ITHit.Events.DispatchEvent(this, 'OnResponse', oResponseData);
        },

        /**
         * Undo deleting file. Works only with ITHit WebDAV DeltaV ReumableUpload Server.
         * @param {string} sPath Item path.
         * @returns {object}
         */
        Undelete: function(sPath) {

            var oRequest = this.CreateRequest(this.__className + '.Undelete()');

            sPath   = ITHit.WebDAV.Client.Encoder.EncodeURI(sPath);
            var oReport = ITHit.WebDAV.Client.Methods.Undelete.Go(oRequest, sPath, ITHit.WebDAV.Client.HierarchyItem.GetHost(sPath));

            oRequest.MarkFinish();
            return oReport;
        },

		/**
         * Sets login and password for WebDAV server authentication.
         *
         * This method call sets credentials for XmlHttpRequest calls. It works with Basic, Digest, NTLM and Kerberos
         * authentication. It does not support Cookies/Forms authentication (because XHR can not handle 302 Found
         * response used in Cookies/Forms).
         * To support Cookies/Forms authentication, detect the WebDAV XHR request on the server side and return 278 response
         * code instead of 302 when authentication is required. You must also set the Location header on the server side.
         * The WebDAV Ajax Library will detect the 278 response and redirect the web page to the URL specified in the Location header.
         * Typically you will also want to set the return URL in the Location header. On the server side you can extract
         * the return URL from the Referer header (the Referer header points to the page on which XHR resides, while the
         * original request Url points to some WebDAV url). Your location header will typically look like this:
         * Location: http://server/login.page?ReturnUrl=http://server/webdav-ajax-lib.page
         * @param {string} sUser User login
         * @param {string} sPass User password
         */
        SetCredentials: function(sUser, sPass) {
            this._User    = sUser;
            this._Pass    = sPass;
        },

        GetIisDetected: function() {
            return this._IsIisDetected;
        },

        /**
        * @private
        */
        GEdit: function (sHref, iTimeout) {
            var oRequest = this.CreateRequest(this.__className + '.GEdit()'); 
            return ITHit.WebDAV.Client.File.GEdit(oRequest, sHref, iTimeout);
        },


        /**
        * @private
        */
        GEditAsync: function (sHref, iTimeout, fCallback) {
            var oRequest = this.CreateRequest(this.__className + '.GEditAsync()');

            ITHit.WebDAV.Client.File.GEditAsync(
                oRequest,
                sHref,
                iTimeout,
                function (oAsyncResult) {     
                    fCallback(oAsyncResult);
                }
            );

            return oRequest;
        },

        /**
        * @private
        */
        GUnlock: function (sHref, sLockToken, sRevisionID) {
            var oRequest = this.CreateRequest(this.__className + '.GUnlock()');

            ITHit.WebDAV.Client.File.GUnlock(oRequest, sHref, sLockToken, sRevisionID);
        },

        /**
        * @private
        */
        GUnlockAsync: function (sHref, sLockToken, sRevisionID, fCallback) {
            var oRequest = this.CreateRequest(this.__className + '.GUnlockAsync()');

            ITHit.WebDAV.Client.File.GUnlockAsync(
                oRequest,
                sHref,
                sLockToken,
                sRevisionID,
                function (oAsyncResult) {
                    fCallback(oAsyncResult);
                }
            );

            return oRequest;
        }

    });

})();
(function() {
    /**
     * Upload state.
     * @api
     * @enum {string}
     * @readonly
     * @class ITHit.WebDAV.Client.Upload.State
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.State',
        null,
        {},
        /** @lends ITHit.WebDAV.Client.Upload.State */ {

            /**
             * Upload in progress.
             * @type {string}
             */
            Uploading: 'Uploading',

            /**
             * Upload aborted.
             * @type {string}
             */
            Canceled: 'Canceled',

            /**
             * Upload paused.
             * @type {string}
             */
            Paused: 'Paused',

            /**
             * Upload queued for upload.
             * @type {string}
             */
            Queued: 'Queued',

            /**
             * Upload failed.
             * @type {string}
             */
            Failed: 'Failed',

            /**
             * Upload completed.
             * @type {string}
             */
            Completed: 'Completed',
            /**
             * Upload scheduled for retry.
             * @type {string}
             */
            Retrying: 'Retrying',

            /**
             * Upload skipped.
             * @type {string}
             */
            Skipped: 'Skipped'
        });
})();

(function() {
    /**
     * This class represents progress state of upload.
     * @api
     * @class ITHit.WebDAV.Client.Upload.Progress
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Progress',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Progress.prototype */
        {

            /**
             * Bytes uploaded.
             * @api
             * @type {!number}
             */
            UploadedBytes: 0,

            /**
             * Total bytes to upload.
             * @api
             * @type {!number}
             */
            TotalBytes: 0,

            /**
             * Elapsed time in seconds.
             * @api
             * @type {!number}
             */
            ElapsedTime: 0,

            /**
             * Time left in seconds.
             * @api
             * @type {!number}
             */
            RemainingTime: 0,

            /**
             * Progress in percents.
             * @api
             * @type {!number}
             */
            Completed: 0,

            /**
             * Speed in bytes/s.
             * @api
             * @type {!number}
             */
            Speed: 0
        });
})();

(function() {
    /**
     * Event names.
     * @enum {string}
     * @readonly
     * @class ITHit.WebDAV.Client.Upload.Events.EventName
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Events.EventName',
        null,
        {},
        /** @lends ITHit.WebDAV.Client.Upload.Events.EventName */ {

            /**
             * OnQueueChanged.
             * @type {string}
             */
            OnQueueChanged: 'OnQueueChanged',
            /**
             * OnStateChanged.
             * @type {string}
             */
            OnStateChanged: 'OnStateChanged',

            /**
             * OnProgressChanged.
             * @type {string}
             */
            OnProgressChanged: 'OnProgressChanged',
            /**
             * @type {string}
             */
            OnError: 'OnError',

            OnUploadItemsCreated: 'OnUploadItemsCreated',

            OnBeforeUploadStarted: 'OnBeforeUploadStarted',

            OnUploadError: 'OnUploadError'
        });
})();

(function() {
    'use strict';

    /**
     * @class ITHit.WebDAV.Client.Upload.Events.BaseEvent
     * @public
     * @abstract
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Events.BaseEvent',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Events.BaseEvent.prototype */
        {

            /**
             * Event name.
             * @public
             * @type {string}
             */
            Name: '',
            /**
             * Event source.
             * @public
             * @type {Object}
             */
            Sender: null
        });
})();


(function() {
    /**
     * This class provides state change event data;
     * @class ITHit.WebDAV.Client.Upload.Events.StateChanged
     * @extends ITHit.WebDAV.Client.Upload.Events.BaseEvent
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Events.StateChanged',
        ITHit.WebDAV.Client.Upload.Events.BaseEvent,
        /** @lends ITHit.WebDAV.Client.Upload.Events.StateChanged.prototype */
        {
            /**
             * Previous state.
             * @type {ITHit.WebDAV.Client.Upload.State}
             */
            OldState: null,

            /**
             * Actual state.
             * @type {ITHit.WebDAV.Client.Upload.State}
             */
            NewState: null,

            constructor: function(oSender, sOldState, sNewState) {
                this.Name = ITHit.WebDAV.Client.Upload.Events.EventName.OnStateChanged;
                this.OldState = sOldState;
                this.NewState = sNewState;
                this.Sender = oSender;
            }
        });
})();


(function() {
    /**
     * This class provides state change event data;
     * @class ITHit.WebDAV.Client.Upload.Events.ProgressChanged
     * @extends ITHit.WebDAV.Client.Upload.Events.BaseEvent
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Events.ProgressChanged',
        ITHit.WebDAV.Client.Upload.Events.BaseEvent,
        /** @lends ITHit.WebDAV.Client.Upload.Events.ProgressChanged.prototype */
        {
            /**
             * Previous progress.
             * @type {ITHit.WebDAV.Client.Upload.Progress}
             */
            OldProgress: null,

            /**
             * Actual progress.
             * @type {ITHit.WebDAV.Client.Upload.Progress}
             */
            NewProgress: null,

            constructor: function(oSender, sOldState, sNewState) {
                this.Name = ITHit.WebDAV.Client.Upload.Events.EventName.OnProgressChanged;
                this.OldProgress = sOldState;
                this.NewProgress = sNewState;
                this.Sender = oSender;
            }
        });
})();


(function() {
    'use strict';

    /**
     * @api
     * Instance of this class provides binding for HTMLElement.
     * @class ITHit.WebDAV.Client.Upload.Controls.HtmlControl
     */
    var staticSelf = ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Controls.HtmlControl',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Controls.HtmlControl.prototype */ {

            /**
             * Id attribute.
             * @api
             * @type {string}
             */
            Id: '',

            /**
             * Associated HTML Element
             * @api
             * @type {HTMLElement}
             */
            HtmlElement: null,

            constructor: function(sElementId) {
                this.Id = sElementId;
                this.HtmlElement = document.getElementById(sElementId);
            },

            /**
             * Prevents propagation and defaults action of the passed event.
             * @param {Event} oEvent
             * @protected
             */
            _StopEvent: function(oEvent) {
                if (oEvent.preventDefault) {
                    oEvent.preventDefault();
                } else {
                    oEvent.returnValue = false;
                }

                if (oEvent.stopPropagation) {
                    oEvent.stopPropagation();
                }
            },

            /**
             * Add event handlers.
             * @public
             * @param {string} sEventName The event name to handle.
             * @param {Function} fCallback The callback to call.
             * @param {Object} [oContext] The context to callback is called with.
             */
            AddListener: function(sEventName, fCallback, oContext) {
                oContext = oContext || null;
                this._CheckEventNameOtThrow(sEventName);
                ITHit.Events.AddListener(this, sEventName, fCallback, oContext);
            },

            /**
             * Removes event listener.
             * @public
             * @param {string} sEventName The event name to remove.
             * @param {Function} fCallback The callback to remove.
             * @param {Object} [oContext] The context to callback is called with.
             */
            RemoveListener: function(sEventName, fCallback, oContext) {
                oContext = oContext || null;
                this._CheckEventNameOtThrow(sEventName);
                ITHit.Events.RemoveListener(this, sEventName, fCallback, oContext);
            },


            _CheckEventNameOtThrow: function(sEventName) {
                if (sEventName !== staticSelf.EVENT_ON_FILE_INPUT_HANDLED) {
                    throw new ITHit.WebDAV.Client.Exceptions.NotFoundEventNameException(sEventName);
                }
            },

            /**
             * @protected
             * @param {ITHit.WebDAV.Client.AsyncResult} oAsyncResult
             */
            _RaiseOnFileInputHandled: function(oAsyncResult) {
                ITHit.Events.DispatchEvent(this, staticSelf.EVENT_ON_FILE_INPUT_HANDLED, [{Source: this, AsyncResult: oAsyncResult}]);
            }
        },
        /** @lends ITHit.WebDAV.Client.Upload.Controls.HtmlControl */{

            /**
             * Event reporting that file handling finished..
             * @public
             * @event ITHit.WebDAV.Client.Upload.Controls.HtmlControl#OnFileInputHandled
             * @property {ITHit.WebDAV.Client.Upload.Controls.HtmlControl} Source The source of event.
             * @property {ITHit.WebDAV.Client.AsyncResult} AsyncResult Result.
             * @property {ITHit.WebDAV.Client.Upload.FSEntry[]} AsyncResult.Result Current uploader
             */
            EVENT_ON_FILE_INPUT_HANDLED: 'OnFileInputHandled'
        });
})();

(function() {
    'use strict';

    var staticSelf = ITHit.DefineClass('ITHit.WebDAV.Client.Upload.FSEntry',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.FSEntry.prototype */
        {


            /**
             * Returns relative path of entry on file system.
             * @public
             * @return {string}
             */
            GetRelativePath: function() {
                return this._RelativePath;
            },

            /**
             * Returns File object or null if entry is directory.
             * @return {File}
             */
            GetFile: function() {
                return this._File || null;
            },

            /**
             * Returns true if folder.
             * @return {boolean}
             */
            IsFolder: function() {
                return !this._File;
            },

            /**
             * Returns true if file.
             * @return {boolean}
             */
            IsFile: function() {
                return !this.IsFolder();
            },

            /**
             * Get File size.
             * @return {number} size of file.
             */
            GetSize: function() {
                if (this.IsFolder()) return 0;
                return this._File.size || this._File.fileSize;
            },

            /**
             * This class represents file or folder in unify form.
             * @public
             * @alias ITHit.WebDAV.Client.Upload.FSEntry
             * @constructs
             *
             * @param {string} sPath The path without resource name.
             * @param {File} [oFile] The file object.
             */
            constructor: function(sPath, oFile) {
                this._RelativePath = sPath;
                this._File = oFile || null;
            },

            /**
             * @type {string}
             */
            _RelativePath: '',

            /**
             * @private
             * @type {File}
             */
            _File: null

        },
        /** @lends ITHit.WebDAV.Client.Upload.FSEntry */
        {
            /**
             * @public
             * @readonly
             */
            PathSeparator: '/',

            /**
             * Creates entry.
             * @public
             * @param {string[]} aPathParts
             * @param {File} [oFile]
             * @return {ITHit.WebDAV.Client.Upload.FSEntry}
             */
            CreateFromPathParts: function(aPathParts, oFile) {
                var sPath = aPathParts.join(staticSelf.PathSeparator);
                return new ITHit.WebDAV.Client.Upload.FSEntry(sPath, oFile);
            }
        });
})();


(function() {
    'use strict';

    /**
     * This class provides methods for creation of {@link ITHit.WebDAV.Client.Upload.FSEntryFactory}s.
     * @public
     * @class ITHit.WebDAV.Client.Upload.Controls.FSEntryFactory
     */
    var self = ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Controls.FSEntryFactory',
        null,
        {},
        /** @lends ITHit.WebDAV.Client.Upload.FSEntryFactory */
        {

            /**
             * Creates entries collection from input object.
             * @public
             * @param {HTMLInputElement} oInput The HTML input element to create from.
             * @param {ITHit.WebDAV.Client.Upload.FSEntryFactory~ResultCallback} fCallback
             */
            CreateFromInputAsync: function(oInput,fCallback) {
                if (!!oInput.webkitEntries && oInput.webkitEntries.length > 0) {
                    var aWebkitEntries = this._GetWebkitEntries(oInput.webkitEntries);
                    if (aWebkitEntries.length > 0) {
                        var aPathParts = [];
                        self._ExtractFromWebkitEntriesAsync(aWebkitEntries, aPathParts, fCallback);
                        return;
                    }
                }

                var aFSEntries = this.CreateFromFileList(oInput.files);
                fCallback(ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult(aFSEntries));
            },

            /**
             * Creates entries collection from data transfer object.
             * @public
             * @param {DataTransfer} oDataTransfer DataTransferList from drag event.
             * @param {ITHit.WebDAV.Client.Upload.FSEntryFactory~ResultCallback} fCallback
             */
            CreateFromDataTransferAsync: function(oDataTransfer, fCallback) {
                if (oDataTransfer.items && oDataTransfer.items.length > 0) {
                    var aWebkitEntries = this._GetWebkitEntries(oDataTransfer.items);
                    if (aWebkitEntries.length > 0) {
                        var aPathParts = [];
                        self._ExtractFromWebkitEntriesAsync(aWebkitEntries, aPathParts, fCallback);
                        return;
                    }
                }

                var aResult = [];
                if (oDataTransfer.files.length > 0) {
                    aResult = self.CreateFromFileList(oDataTransfer.files);
                }

                fCallback(ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult(aResult));
            },

            /**
             * Creates entries collection from file list object.
             * @public
             * @param {FileList} aFiles
             * @return {ITHit.WebDAV.Client.Upload.FSEntry[]}
             */
            CreateFromFileList: function(aFiles) {
                var aFSEntries = [];
                for (var i = 0; i < aFiles.length; i++) {
                    var oFile = aFiles[i];
                    var sPath = '/' + (oFile.webkitRelativePath || oFile.name);
                    var FSEntry = new ITHit.WebDAV.Client.Upload.FSEntry(sPath, oFile);
                    aFSEntries.push(FSEntry);
                }
                return aFSEntries;
            },
            
            _GetWebkitEntries: function(aItems) {
                var aEntries = [];
                for (var i = 0; i < aItems.length; i++) {
                    var oItem = aItems[i];
                    var oEntry = oItem.webkitGetAsEntry &&
                        oItem.webkitGetAsEntry();
                    if (oEntry) {
                        aEntries.push(oEntry);
                    }
                }
                return aEntries;
            },

            _ExtractFromWebkitEntriesAsync: function(aWebkitEntries, aPathParts, fCallback) {
                if (aWebkitEntries.length === 0) {
                    aPathParts.push('');
                    var oFSEntry = new ITHit.WebDAV.Client.Upload.FSEntry.CreateFromPathParts(aPathParts);
                    fCallback(ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult([oFSEntry]));
                }

                var aEntries = [];
                var iIterations = aWebkitEntries.length;
                for (var i = 0; i < aWebkitEntries.length; i++) {
                    var oWebkitEntry = aWebkitEntries[i];
                    self._ExtractFromWebkitEntryAsync(oWebkitEntry, aPathParts.slice(), function(oAsyncResult) {
                        iIterations--;
                        if (!oAsyncResult.IsSuccess) {
                            iIterations = 0;
                            fCallback(oAsyncResult);
                            return;
                        }

                        aEntries = aEntries.concat(oAsyncResult.Result);
                        if (iIterations <= 0) {
                            fCallback(ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult(aEntries));
                        }
                    });
                }
            },

            _ExtractFromWebkitEntryAsync: function(oEntry, aPathParts, fCallback) {
                if (oEntry.isDirectory) {
                    self._ExtractWebkitDirectoryChildrenAsync(oEntry, aPathParts.slice(), function(oAsyncResult) {
                        if (oAsyncResult.IsSuccess) {
                            fCallback(oAsyncResult);
                        } else {
                            fCallback(ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult(oAsyncResult.Result));
                        }
                    });
                } else {
                    oEntry.file(function(file) {
                        aPathParts.push(file.name);
                        var oFSEntry = new ITHit.WebDAV.Client.Upload.FSEntry.CreateFromPathParts(aPathParts, file);
                        fCallback(ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult(oFSEntry));
                    }, function(oFileError) {
                        fCallback(ITHit.WebDAV.Client.AsyncResult.CreateFailedResult(oFileError));
                    });
                }
            },

            _ExtractWebkitDirectoryChildrenAsync: function(oWebKitDirectory, sPathParts, fCallback) {
                var dirReader = oWebKitDirectory.createReader();
                dirReader.readEntries(function(entries) {
                    sPathParts.push(oWebKitDirectory.name);
                    self._ExtractFromWebkitEntriesAsync(entries, sPathParts, fCallback);
                }, function errorHandler(oException) {
                    fCallback(ITHit.WebDAV.Client.AsyncResult.CreateFailedResult(oException));
                });
            }
        }
    );
})();

/**
 * Callback to get result.
 * @callback ITHit.WebDAV.Client.Upload.FSEntryFactory~ResultCallback
 * @param {ITHit.WebDAV.Client.AsyncResult} AsyncResult Result of creation. Contains array of {@link ITHit.WebDAV.Client.Upload.FSEntry}s.
 * @param {ITHit.WebDAV.Client.Upload.FSEntry} AsyncResult.Result
 */

(function() {
    'use strict';

    /**
     * Instance of this class provides metadata for drop zone.
     * @api
     * @class ITHit.WebDAV.Client.Upload.Controls.DropZone
     * @extends ITHit.WebDAV.Client.Upload.Controls.HtmlControl
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Controls.DropZone',
        ITHit.WebDAV.Client.Upload.Controls.HtmlControl,
        /** @lends  ITHit.WebDAV.Client.Upload.Controls.DropZone.prototype */ {

            constructor: function(sElementId) {
                this._super(sElementId);
                this.HtmlElement.addEventListener('drop', ITHit.Utils.MakeScopeClosure(this, '_OnDropHandler'), false);
                this.HtmlElement.addEventListener('dragover', ITHit.Utils.MakeScopeClosure(this, '_OnDragOverHandler'), false);
                this.HtmlElement.addEventListener('dragenter', ITHit.Utils.MakeScopeClosure(this, '_OnDragEnterHandler'), false);
            },

            /**
             * @param {Event} oEvent
             * @private
             */
            _OnDropHandler: function(oEvent) {
                this._StopEvent(oEvent);
                ITHit.WebDAV.Client.Upload.Controls.FSEntryFactory.CreateFromDataTransferAsync(oEvent.dataTransfer, this._RaiseOnFileInputHandled.bind(this));
            },

            _OnDragEnterHandler: function(oDragEvent) {
                this._StopEvent(oDragEvent);
            },

            _OnDragOverHandler: function(oDragEvent) {
                if (ITHit.DetectBrowser.IE && (ITHit.DetectBrowser.IE < 10)) {
                    this._StopEvent(oDragEvent);
                }
                var dt = oDragEvent.dataTransfer;
                if (!dt) {
                    this._StopEvent(oDragEvent);
                }

                var dtTypes = dt.types;
                if (dtTypes) {
                    // FF
                    if (dtTypes.contains && !dtTypes.contains('Files')) return;
                    // Chrome
                    if (dtTypes.indexOf &&
                        (-1 == dtTypes.indexOf('Files'))) return;
                }

                dt.dropEffect = 'copy';

                this._StopEvent(oDragEvent);
            }
        }
    );
})();

/**
 * Instance of this class provides metadata for input.
 * @class ITHit.WebDAV.Client.Upload.Controls.Input
 * @extends ITHit.WebDAV.Client.Upload.Controls.HtmlControl
 * @api
 */
(function() {
    'use strict';
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Controls.Input',
        ITHit.WebDAV.Client.Upload.Controls.HtmlControl,
        /** @lends  ITHit.WebDAV.Client.Upload.Controls.Input.prototype */ {

            constructor: function(sElementId) {
                this._super(sElementId);
                this.HtmlElement.addEventListener('change', ITHit.Utils.MakeScopeClosure(this, '_OnChange'), false);
            },

            /**
             * @param {Event} oEvent
             * @private
             */
            _OnChange: function(oEvent) {
                if (!oEvent.target.value) return;
                this._StopEvent(oEvent);
                ITHit.WebDAV.Client.Upload.Controls.FSEntryFactory.CreateFromInputAsync(oEvent.target, function(oAsyncResult) {
                    this._RaiseOnFileInputHandled(oAsyncResult);
                    oEvent.target.value= '';
                }.bind(this));
            }
        }
    );
})();

(function() {
    'use strict';
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Collections.Pair',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Collections.Pair.prototype */
        {
            /**
             * The key property of the Pair.
             * @type {string}
             */
            Key: '',
            /**
             * The value property of the Pair.
             * @type {T}
             */
            Value: null,

            /**
             * @public
             * @class ITHit.WebDAV.Client.Upload.Collections.Pair
             * @classdesc Holds key-value pair.
             * @constructs
             * @template {T}
             * @property {string} [sKey] The key property of the Pair.
             * @property {T} [oValue] The value property of the Pair.
             * Creates new Pair.
             */
            constructor: function(sKey, oValue) {
                this.Key = sKey;
                this.Value = oValue;
            },
        });
})();

(function() {
    'use strict';
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Collections.Map',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Collections.Map.prototype */
        {
            /**
             * @private
             * @type {Object<string, T>}
             */
            _UnderLayingObject: null,

            /**
             * @private
             * @type {number}
             */
            _Length: 0,

            /**
             * Creates new Map.
             * @public
             * @class ITHit.WebDAV.Client.Upload.Collections.Map
             * @classdesc Holds key-value pairs.
             * @constructs
             * @template T
             * @param {Array.<ITHit.WebDAV.Client.Upload.Collections.Pair.<T>>} [aPairs] Array of pairs.
             */
            constructor: function(aPairs) {
                this._UnderLayingObject = {};
                aPairs = aPairs || [];
                for (var i = 0; i < aPairs.length; i++) {
                    var oPair = aPairs[i];
                    this.Set(oPair.Key, oPair.Value);
                }
            },

            /**
             * Removes all elements from a Map object.
             */
            Clear: function() {
                this._UnderLayingObject = {};
                this._Length = 0;
            },

            /**
             * Removes the specified element from a Map object.
             * @public
             * @param {string} sKey The key of the element to remove from the Map object.
             * @return {boolean} Returns true if an element in the Map object existed and has been removed, or false if the element does not exist.
             */
            Delete: function(sKey) {
                // todo add type and nullability check
                if (!this.Has(sKey)) return false;
                delete this._UnderLayingObject[sKey];
                this._Length--;
                return true;
            },

            /**
             * Returns a new Array object that contains the [Pair]{@link ITHit.WebDAV.Client.Upload.Collections.Pair} for each element in the Map.
             * @return {Array.<ITHit.WebDAV.Client.Upload.Collections.Pair.<T>>} Array of the keys-value pairs.
             */
            Entries: function() {
                var aResultKeys = [];
                var aKeys = this.Keys();
                for (var i = 0; i < aKeys.length; i++) {
                    var sKey = aKeys[i];
                    aResultKeys.push(new ITHit.WebDAV.Client.Upload.Collections.Pair(sKey, this._UnderLayingObject[sKey]));
                }

                return aResultKeys;
            },

            /**
             * Returns a specified element from a Map object.
             * @param {string} sKey  The key of the element to return from the Map object.
             * @return {T} Returns the element associated with the specified key or undefined if the key can't be found in the Map object.
             */
            Get: function(sKey) {
                return this._UnderLayingObject[sKey];
            },

            /**
             * Returns a boolean indicating whether an element with the specified key exists or not.
             * @param {string} sKey The key of the element to test for presence in the Map object.
             * @return {boolean} Returns true if an element with the specified key exists in the Map object; otherwise false.
             */
            Has: function(sKey) {
                return !!this.Get(sKey);
            },

            /**
             * Returns a new Array object that contains the keys for each element in the Map.
             * @return {string[]} Array of the keys.
             */
            Keys: function() {
                /** @type {string[]} */
                var aKeys = [];
                for (var sKey in this._UnderLayingObject) {
                    if (Object.prototype.hasOwnProperty.call(this._UnderLayingObject, sKey)) {
                        aKeys.push(sKey);
                    }
                }

                return aKeys;
            },
            /**
             * Adds or updates an element with a specified key and value to a Map object.
             * @param {string} sKey The key of the element to add to the Map object.
             * @param {T} oValue The value of the element to add to the Map object.
             * @return {ITHit.WebDAV.Client.Upload.Collections.Map} The Map object.
             */
            Set: function(sKey, oValue) {
                if (!this.Has(sKey)) this._Length++;
                this._UnderLayingObject[sKey] = oValue;
                return this;
            },
            /**
             * Returns a new Array object that contains the values for each element in the Map
             * @return {Array.<T>} Array of the values.
             */
            Values: function() {
                var aValues = [];
                for (var sKey in this._UnderLayingObject) {
                    if (Object.prototype.hasOwnProperty.call(this._UnderLayingObject, sKey)) {
                        aValues.push(this._UnderLayingObject[sKey]);
                    }
                }
                return aValues;
            },

            /**
             * Returns the number of elements in a Map object.
             * @return {number}
             */
            Count: function() {
                return this._Length;
            },


            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Collections.Map~ForEachCallBack<T>} fCallBack
             * @param {Object} [thisArg] Value to use as this when executing fCallBack.
             */
            ForEach: function(fCallBack, thisArg) {
                var aEntries = this.Entries();
                aEntries.forEach(function(oElement){
                    fCallBack.call(thisArg, oElement.Value, oElement.Key, this);
                }, this);
            }
        });
})();

/**
 * Callback function to be called on each item.
 * @public
 * @template T
 * @callback ITHit.WebDAV.Client.Upload.Collections.Map~ForEachCallBack
 * @param {T} value
 * @param {string} key
 * @param {ITHit.WebDAV.Client.Upload.Collections.Map<T>} map
 */

(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Providers.UploadDiff',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Providers.UploadDiff.prototype */
        {
            /**
             * @public
             * @type {number}
             */
            BytesUploaded: 0,

            /**
             * @public
             * @type {number}
             */
            TimeUpload: 0,

            /**
             * @class ITHit.WebDAV.Client.Upload.Providers.UploadDiff
             * @constructs
             * @param {number} oBytesUploaded
             * @param {number} oTimeUpload
             * @param {Date} oTimeStamp
             */
            constructor: function(oBytesUploaded, oTimeUpload, oTimeStamp ) {
                this.BytesUploaded = oBytesUploaded;
                this.TimeUpload = oTimeUpload;
            }

        });
})();


(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Providers.ProgressTracker',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Providers.ProgressTracker.prototype */
        {

            /**
             * Upload history length to analyse.
             * @private
             * @type {number}
             * @readonly
             * @default
             */
            _DiffCount: 5,
            _IsCompleted: false,

            /**
             * Creates new ProgressTracker.
             * @public
             * @alias ITHit.WebDAV.Client.Upload.Providers.ProgressTracker
             * @classdesc Provides methods for perform progress tracking. Tracking performed by url.
             * @constructs
             * @param {number} iSize File size.
             */
            constructor: function(iSize) {
                this.ResetSpeed();
                this._Size = iSize;
                this._StartPosition = 0;
                this._CurrentProgress = new ITHit.WebDAV.Client.Upload.Progress();
                this._CurrentProgress.TotalBytes = iSize;
            },

            /**
             * Return current progress.
             * @public
             * @return {ITHit.WebDAV.Client.Upload.Progress} Current progress.
             */
            GetProgress: function() {
                return this._CurrentProgress;
            },

            _CalculateProgress: function() {
                var fUploadSpeed = this._GetSpeed();
                var oNewProgress = new ITHit.WebDAV.Client.Upload.Progress();
                oNewProgress.TotalBytes = this._Size;
                oNewProgress.UploadedBytes = this._BytesUploaded;
                oNewProgress.Speed = Math.floor((Math.round(fUploadSpeed * 10) / 10));
                oNewProgress.Completed = this._GetUploadedPercents();
                oNewProgress.ElapsedTime = Math.floor(this._ElapsedTime);

                if (fUploadSpeed) {
                    oNewProgress.RemainingTime = this._GetRemainingTime(fUploadSpeed);
                }

                return oNewProgress;
            },

            /**
             * @return {number}
             */
            _GetSpeed: function() {
                if (!this.IsCountable()) return 0;
                var aLastDiffSlice = this._Diffs.slice(-1 * this._DiffCount);

                // Calculate average upload speed
                var iSummaryBytesUploaded = 0;
                var iSummaryTimeUpload = 0;
                for (var i = 0, l = aLastDiffSlice.length; i < l; i++) {
                    iSummaryBytesUploaded += aLastDiffSlice[i].BytesUploaded;
                    iSummaryTimeUpload += aLastDiffSlice[i].TimeUpload;
                }

                var fUploadSpeed = iSummaryBytesUploaded / iSummaryTimeUpload;
                return (fUploadSpeed > 0) ? fUploadSpeed : 0;
            },
            _GetUploadedPercents: function() {
                if (!this.IsCountable()) return this._IsCompleted ? 100 : 0;
                return Math.floor((this._BytesUploaded) / (this._Size) * 100);
            },
            _GetRemainingTime: function(fUploadSpeed) {
                var iTimeLeft = Math.ceil((this._Size - this._BytesUploaded) / fUploadSpeed);
                return Math.floor(iTimeLeft);
            },

            _Notify: function() {
                var oEvent = new ITHit.WebDAV.Client.Upload.Events.ProgressChanged(this, this._OldProgress, this._CurrentProgress);
                ITHit.Events.DispatchEvent(this, 'OnProgress', [oEvent]);
            },

            UpdateBytes: function(iBytesUploaded, iBytesTotal) {
                var oNow = new Date();
                var iCurrentBytesUploaded = iBytesUploaded + this._StartPosition - this._LastUploadedBytes;
                var iTimeUpload = (oNow - this._LastReportTime) / 1000;
                var oDiffInfo = new ITHit.WebDAV.Client.Upload.Providers.UploadDiff(iCurrentBytesUploaded, iTimeUpload);
                this._Diffs.push(oDiffInfo);
                this._BytesUploaded = iBytesUploaded + this._StartPosition;
                this._LastUploadedBytes = iBytesUploaded + this._StartPosition;
                this._LastReportTime = oNow;
                this._ElapsedTime += iTimeUpload;
                this._OldProgress = this._CurrentProgress;
                this._CurrentProgress = this._CalculateProgress();
                this._Notify();
            },
            IsCountable: function() {
                return this._Size !== 0;
            },
            _Set: function(BytesUploaded, TotalContentLength) {
                var oNow = new Date();
                var iTimeUpload = (oNow - this._LastReportTime) / 1000;
                this.ResetSpeed();
                this._BytesUploaded = BytesUploaded;
                this._LastUploadedBytes = 0;
                this._LastReportTime = oNow;
                this._ElapsedTime += iTimeUpload;
                this._OldProgress = this._CurrentProgress;
                this._CurrentProgress = this._CalculateProgress();
                this._Notify();
            },
            OnProgressChanged: function(fCallback, oContext) {
                ITHit.Events.AddListener(this, 'OnProgress', fCallback, oContext);
            },

            IsCompleted: function() {
              return this._BytesUploaded === this._Size;
            },

            Reset: function() {
                this._StartPosition = 0;
                this._BytesUploaded = 0;
                this._OldProgress = this._CurrentProgress;
                this._CurrentProgress = this._CalculateProgress();
                this._Notify();
            },

            /**
             * Begins track progress from selected position.
             * @param {number} [iStart=0] The start position of the upload session.
             */
            StartTracking: function(iStart) {
                iStart = iStart || this._CurrentProgress.UploadedBytes;
                this._StartPosition = iStart;
            },

            /**
             * Stops track progress.
             */
            StopTracking: function() {
                this.ResetSpeed();
                this._OldProgress = this._CurrentProgress;
                this._CurrentProgress.Speed = 0;
                this._Notify();
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.UploadProgressInfo} oServerProgress
             */
            SyncProgress: function(oServerProgress) {
                if (oServerProgress.BytesUploaded <
                    this._StartPosition) {
                    this.ResetSpeed();
                    this._StartPosition = oServerProgress.BytesUploaded;
                }

                this._Set(oServerProgress.BytesUploaded, oServerProgress.TotalContentLength);
            },

            /**
             * @param {Date} [oDate]
             */
            ResetSpeed: function(oDate) {
                this._LastReportTime = oDate || new Date();
                this._LastUploadedBytes = 0;
                this._Diffs = [];
            },

            ResetIfComplete: function() {
                if (this.IsCompleted()) {
                    this.Reset();
                }
            },

            SetCompleted: function() {
                this.UpdateBytes(this._Size, this._Size);
            },

            /**
             * Upload history.
             * @public
             * @type {ITHit.WebDAV.Client.Upload.Providers.UploadDiff[]}
             */
            _Diffs: [],

            /**
             * The total size of upload.
             * @public
             * @type {number}
             */
            _Size: 0,

            /**
             * Date when wal last progress history update.
             * @private
             * @type {Date}
             */
            _LastReportTime: null,

            /**
             * @private
             * @type {number}
             */
            _StartPosition: 0,

            /**
             * @private
             * @type {number}
             */
            _BytesUploaded: 0,

            /**
             * @private
             * @type {number}
             */
            _LastUploadedBytes: 0,

            /**
             * @type {ITHit.WebDAV.Client.Upload.Progress}
             */
            _CurrentProgress: null,

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Progress}
             */
            _OldProgress: null,

            /**
             * @type {number}
             */
            _ElapsedTime: 0

        });
})();

(function() {
    'use strict';

    /**
     * @api
     * This object represent base class for parameters of events that is waiting for user action.
     * @class ITHit.WebDAV.Client.Upload.Events.AsyncEvent
     * @extends ITHit.WebDAV.Client.Upload.Events.BaseEvent
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Events.AsyncEvent',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Events.AsyncEvent.prototype */
        {

            constructor: function(oSender, fCallback) {
                this.Sender = oSender;
                this._HandledCallback = fCallback || ITHit.Utils.NoOp;
                this._IsHandled = false;
            },

            /**
             * Event name.
             * @api
             * @type {string}
             */
            Name: '',
            /**
             * Event source.
             * @api
             * @type {Object}
             */
            Sender: null,

            /**
             * @private
             * @type {Function}
             */
            _HandledCallback: null,

            /**
             * @protected
             * @param {Object} [oResult]
             */
            _Handle: function(oResult) {
                if(this._IsHandled) return;
                this._IsHandled = true;
                this._HandledCallback(oResult);
            },

            /**
             * This methods return value that indicates that event already processed.
             * @api
             * @return {boolean} - True if event was processed, false otherwise.
             */
            GetIsHandled: function(){
                return this._IsHandled;
            },

            /**
             * Indicates that event already processed.
             * @protected
             * @type {boolean}
             */
            _IsHandled: false
        });
})();


(function() {
    'use strict';

    /**
     * This object is passed to {@link ITHit.WebDAV.Client.Upload.UploadItem#event:OnBeforeUploadStarted}.
     * You can validate these item as well as specify if item should be overwritten.
     * To continue upload the {@link ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted#Upload} function should be called.
     * To skip upload the {@link ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted#Skip} function should be called.
     * @api
     * @class ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted
     * @extends ITHit.WebDAV.Client.Upload.Events.AsyncEvent
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted',
        ITHit.WebDAV.Client.Upload.Events.AsyncEvent,
        /** @lends ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted.prototype */
        {

            /**
             * Change item state to {@link ITHit.WebDAV.Client.Upload.State.Skipped}.
             * @api
             */
            Skip: function() {
                if (this._IsHandled) return;
                this.Sender.SetSkip();
                this._Handle();
            },


            /**
             * Overwrites item. Ends callback handling.
             */
            Overwrite: function() {
                if (this._IsHandled) return;
                if (!this.Sender.IsFolder()) {
                    this.Sender.SetOverwrite(true);
                }

                this._Handle();
            },

            /**
             * Skips all items. Ends callback handling.
             */
            SkipAll: function() {
                if (this._IsHandled) return;
                var oGroup = this.Sender.GetGroup();
                if (oGroup) {
                    oGroup.GetItems().forEach(function(value) { value.SetSkip(); })
                } else {
                    this.Sender.SetSkip();
                }

                this._Handle();
            },

            /**
             * Overwrites all items. Ends callback handling.
             */
            OverwriteAll: function() {
                if (this._IsHandled) return;
                var oGroup = this.Sender.GetGroup();
                if (oGroup) {
                    oGroup.GetItems().forEach(function(value) { value.SetOverwrite(true); })
                } else {
                    this.Sender.SetOverwrite(true);
                }

                this._Handle();
            },


            /**
             * Continues items upload.
             * If item should not upload call {@link ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted#Skip} method.
             * If any items in the upload list should be overwritten call {@link ITHit.WebDAV.Client.Upload.UploadItem#SetOverwrite(true)} on item.
             * @api
             */
            Upload: function() {
                if (this._IsHandled) return;
                this._Handle();
            },

            constructor: function(oSender, fCallback) {
                this.Name = ITHit.WebDAV.Client.Upload.Events.EventName.OnBeforeUploadStarted;
                this._super(oSender, fCallback);
            }
        });
})();


(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Path.PathCache',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Path.PathCache.prototype */ {
           
           /**
             * @alias ITHit.WebDAV.Client.Upload.Path.PathCache
             * @constructs
             */
            constructor: function(){
             this._UrlMap = new ITHit.WebDAV.Client.Upload.Collections.Map();
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             * @return {boolean}
             */
            Has: function(oUrl) {
                return this._UrlMap.Has(oUrl.GetHref());
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             */
            Add: function(oUrl) {
                this._UrlMap.Set(oUrl.GetHref(), oUrl);
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             */
            Delete: function(oUrl) {
                this._UrlMap.Delete(oUrl.GetHref());
            },

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Collections.Map<ITHit.WebDAV.Client.Upload.Utils.DavUrl>}
             */
            _UrlMap: null
        });
})();

(function() {
    'use strict';

var staticSelf = ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Groups.Group',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Groups.Group.prototype */
        {
            /**
             * @public
             * @readonly
             * @type {number}
             */
            ID: 0,

            /**
             * @public
             * @readonly
             * @type {string}
             */
            IDString:'',

            /**
             * @alias ITHit.WebDAV.Client.Upload.Groups.Group
             * @constructs
             * @param {ITHit.WebDAV.Client.Upload.Collections.Map<ITHit.WebDAV.Client.Upload.Groups.Group[]>} oItemGroupMap
             * @param {ITHit.WebDAV.Client.Upload.Collections.Map<ITHit.WebDAV.Client.Upload.UploadItem[]>} oGroupItemMap
             */
            constructor: function(oItemGroupMap, oGroupItemMap){
                this._ItemGroupMap = oItemGroupMap;
                this._GroupItemMap = oGroupItemMap;
                this.ID = ++staticSelf._GroupCounter;
                this.IDString = this.ID.toString();
                this.PathMap = new ITHit.WebDAV.Client.Upload.Path.PathCache();
            },

            /**
             * @public
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} [oItems]
             */
            AddRange: function(oItems){
                var oCollection = this._GroupItemMap.Get(this.IDString);
                oItems.forEach(function(oItem) {
                    this._ItemGroupMap.Set(oItem.GetUrl(), this);
                    oCollection.push(oItem);
                }.bind(this));
            },

            /**
             * @public
             * @return ITHit.WebDAV.Client.Upload.UploadItem[]
             */
            GetItems: function(){
               return this._GroupItemMap.Get(this.IDString);
            },

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Collections.Map<ITHit.WebDAV.Client.Upload.UploadItem>}
             */
            _GroupItemMap: null,

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Collections.Map<ITHit.WebDAV.Client.Upload.Groups.Group>}
             */
            _ItemGroupMap: null,

            /**
             * @public
             * @type {ITHit.WebDAV.Client.Upload.Path.PathCache}
             */
            PathMap: null
        },
        /** @lends ITHit.WebDAV.Client.Upload.Groups.Group */
        {
            /**
             * @private
             * @type {number}
             */
            _GroupCounter: 0
        });
})();

(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Groups.GroupManager',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Groups.GroupManager.prototype */
        {


            /**
             * @classdesc Manage groups
             * @alias ITHit.WebDAV.Client.Upload.Groups.GroupManager
             * @constructs
             */
            constructor: function() {
                this._GroupItemMap = new ITHit.WebDAV.Client.Upload.Collections.Map();
                this._ItemGroupMap = new ITHit.WebDAV.Client.Upload.Collections.Map();
            },

            /**
             * @public
             * @return {ITHit.WebDAV.Client.Upload.Groups.Group}
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} [oItems]
             */
            CreateGroup: function(oItems){
                oItems = oItems || [];
                var oGroup = new ITHit.WebDAV.Client.Upload.Groups.Group(this._ItemGroupMap, this._GroupItemMap);
                this._GroupItemMap.Set(oGroup.IDString, []);
                oGroup.AddRange(oItems);
                return oGroup;
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.UploadItem} oItem
             * @return {null|ITHit.WebDAV.Client.Upload.Groups.Group[]}
             * @constructor
             */
            GetGroupByItem: function(oItem){
                return this._ItemGroupMap.Get(oItem.GetUrl());
            },

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Collections.Map<ITHit.WebDAV.Client.Upload.UploadItem[]>}
             */
            _GroupItemMap: null,

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Collections.Map<ITHit.WebDAV.Client.Upload.Groups.Group[]>}
             */
            _ItemGroupMap: null
        });
})();

(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Utils.DavUrl',
        Object,
        /** @lends ITHit.WebDAV.Client.Upload.Utils.DavUrl.prototype */ {
            /**
             * The original url string.
             * @private
             * @type {string}
             */
            _OriginalUrl: '',

            /**
             * @type {string}
             */
            _BaseUrl: '',

            /**
             * Scheme
             * @private
             * @type {string}
             */
            _Scheme: '',
            /**
             * Anchor fragment.
             * @private
             * @type {string}
             */
            _Fragment: '',


            /**
             * Port
             * @private
             * @type {string}
             */
            _Port: '',

            /**
             * Host
             * @private
             * @type {string}
             */
            _HostName: '',

            /**
             * Path
             * @private
             * @type {string}
             */
            _Path: '',
            /**
             * Queue
             * @private
             * @type {string}
             */
            _Query: '',
            /**
             * User name
             * @private
             * @type {string}
             */
            _UserName: '',
            /**
             * Password
             * @private
             * @type {string}
             */
            _Password: '',
            /**
             * Relative Path
             * @private
             * @type {string}
             */
            _RelativePath: '',

            /**
             * Resource name
             * @private
             * @type {string}
             */
            _Name: '',

            /**
             * Gets fragment identifier.
             * @public
             * @return {string} The string containing a '#' followed by the fragment identifier of the URL.
             */
            GetHash: function() {
                return this._Fragment;
            },
            /**
             * Gets the host.
             * @public
             * @return {string} The domain (that is the hostname) followed by (if a port was specified) a ':' and the port of the URL.
             */
            GetHost: function() {
                if (this._Port) {
                    return this._HostName + this._PortSeparator + this._Port;
                }

                return this._HostName;
            },

            /**
             * Gets the origin.
             * @public
             * @return {string} Returns a string containing the origin of the URL, that is its scheme, its domain and its port.
             */
            GetOrigin: function() {
                return this.GetProtocol() + this.GetHost();
            },

            /**
             * Gets the name of host.
             * @public
             * @return {string} The domain of the URL.
             */
            GetHostName: function() {
                return this._HostName;
            },
            /**
             * Gets the port if specified.
             * @public
             * @return {string} The port number of the URL.
             */
            GetPort: function() {
                return this._Port;
            },

            /**
             * Gets the protocol if specified.
             * @public
             * @return {string} The protocol scheme of the URL, including the final ':'
             */
            GetProtocol: function() {
                return this._Scheme;
            },

            /**
             * Gets query params if specified.
             * @public
             * @return {string} The query string contained in the URL.
             */
            GetQuery: function() {
                return this._Query;
            },
            /**
             * Gets the name.
             * @public
             * @return {string} The name of resource contained in the URL.
             */
            GetName: function() {
                return this._Name;
            },

            /**
             * Gets the relative path.
             * @public
             * @return {string} The relative path of resource contained in the URL.
             */
            GetRelativePath: function() {
                return this._RelativePath;
            },

            /**
             * Gets the whole URL.
             * @public
             * @return {string} The string containing the whole URL.
             */
            GetHref: function() {
                return this._OriginalUrl;
            },

            /**
             * Gets base path of URL.
             * @public
             * @return {string} The string containing the base path of URL.
             */
            GetBaseUrl: function() {
                return this._BaseUrl;
            },

            /**
             * @override
             */
            toString: function() {
                return this._OriginalUrl;
            },

            Clone: function() {
                return new ITHit.WebDAV.Client.Upload.Utils.DavUrl(this._RelativePath, this._BaseUrl);
            },

            _ParseAuthPartsUndetectedScheme: function(sString) {
                var aParts = sString.split(':');
                if (aParts.length === 3) {
                    this._Scheme = aParts[0] + ':';
                    this._UserName = aParts[1];
                    this._Password = aParts[2];
                } else if (aParts.length === 2) {
                    this._Scheme = aParts[0];
                    this._UserName = aParts[1];
                } else {
                    this._UserName = aParts[0];
                }
            },
            _ParseAuthPartsDetectedScheme: function(sString) {
                var aParts = sString.split(':');
                if (aParts.length === 2) {
                    this._UserName = aParts[0];
                    this._Password = aParts[1];
                } else {
                    this._UserName = aParts[0];
                }
            },
            ParseAuthorityWithScheme: function(sString, bSchemeAlreadyParsed) {
                var aPortMatched = sString.match(this._PortRexEx);
                if (aPortMatched) {
                    this._Port = aPortMatched[0].slice(1);
                    sString = sString.slice(0, -aPortMatched[0].length);
                }

                var aAuthorityParts = sString.split('@');
                if (aAuthorityParts.length > 1) {
                    this._HostName = aAuthorityParts[1];
                    if (!bSchemeAlreadyParsed) {
                        this._ParseAuthPartsUndetectedScheme(aAuthorityParts[0]);
                    } else {
                        this._ParseAuthPartsDetectedScheme(aAuthorityParts[0]);
                    }

                    return;
                }

                var aParts = aAuthorityParts[0].split(':');
                if (aParts.length > 1) {
                    this._Scheme = aParts[0] + ':';
                    this._HostName = aParts[1];
                    return;
                }

                this._HostName = sString;
            },
            _ParseTrailingPathPart: function(sString) {
                var aFragmentParts = sString.split(this._FragmentSeparator);
                if (aFragmentParts.length > 1) {
                    this._Fragment = this._FragmentSeparator + aFragmentParts[1];
                }

                var aQueryParts = aFragmentParts[0].split('?');
                if (aQueryParts.length > 1) {
                    this._Query = aQueryParts[1];
                    return aQueryParts[0];
                }

                return aQueryParts[0];
            },
            _ParseUrl: function(sUrl) {
                var aParts = sUrl.split(this._DashedSchemeSeparator);
                if (aParts.length > 1) {
                    this._Scheme = aParts[0] + this._DashedSchemeSeparator;
                    this._IsDashedScheme = true;
                    aParts.splice(0, 1);
                }

                var sPathParts = aParts[0].split(this._PathSeparator);

                sPathParts = ITHit.Utils.FilterBy(sPathParts, function(oElement) {
                    return oElement !== '';
                });

                this.ParseAuthorityWithScheme(sPathParts[0], this._IsDashedScheme);
                sPathParts.splice(0, 1);
                if (sPathParts.length === 0) return;

                var aResultPath = [];
                for (var i = 0; i < aParts.length - 1; i++) {
                    aResultPath.push(sPathParts[i]);
                }

                var lastPart = this._ParseTrailingPathPart(sPathParts[sPathParts.length - 1]);
                aResultPath.push(lastPart);
                this._Name = lastPart;
                this._Path = this._PathSeparator + aResultPath.join(this._PathSeparator);
                this._RelativePath = this._RelativePath || this._Path;
            },

            /**
             * Creates and return a DavUrl object composed from the given parameters.
             * @classdesc The DavUrl represents an object providing methods used for retrieving url details.
             * @public
             * @class ITHit.WebDAV.Client.Upload.Utils.DavUrl
             * @constructs
             * @param {string} sUrl
             * @param {string} [sBaseUrl]
             */
            constructor: function(sUrl, sBaseUrl) {
                this._BaseUrl = sBaseUrl || '';
                this._OriginalUrl = sUrl;
                if (!!sBaseUrl) {
                    this._RelativePath = this._PathSeparator + this._GetWithoutLeadingSeparator(sUrl);
                    this._OriginalUrl = this._GetWithoutTrailingSeparator(sBaseUrl) + this._RelativePath;
                }

                this._ParseUrl(this._OriginalUrl);
            },

            _PathSeparator: '/',
            _DashedSchemeSeparator: '://',
            _FragmentSeparator: '#',
            _PortRexEx: /:\d+$/,
            _IsDashedScheme: false,
            _PortSeparator: ':',


            _GetWithoutTrailingSeparator: function(sString) {
                var sLastSymbol = sString.slice(-1);
                if (sLastSymbol === this._PathSeparator) {
                    return sString.slice(0, -1);
                }

                return sString;
            },

            _GetWithoutLeadingSeparator: function(sString) {
                var sLeadingSymbol = sString[0];
                if (sLeadingSymbol === this._PathSeparator) {
                    return sString.substring(1);
                }

                return sString;
            }
        });
})();


/**
 * Event reporting that upload item state changed.
 * @api
 * @event ITHit.WebDAV.Client.Upload.UploadItem#OnStateChanged
 * @property {ITHit.WebDAV.Client.Upload.UploadItem} Sender Upload item instance.
 * @property {string} Name Event name.
 * @property {ITHit.WebDAV.Client.Upload.State} OldState Previous state.
 * @property {ITHit.WebDAV.Client.Upload.State} NewState Actual state.
 * @example
 * /&#x002A&#x002A @typedef {ITHit.WebDAV.Client.Upload.UploadItem} oItem &#x002A/
 * var oItem = oUploader.Queue.GetByUrl(sSomeUrl);
 * oItem.AddListener('OnStateChanged', function (oStateChanged) {
 *         console.log('Upload to:' + oStateChanged.Sender.GetUrl() +  ', changed state to :' + oStateChanged.NewState);
 *     });
 *
 */

/**
 * Event reporting that upload item progress changed.
 * @api
 * @event ITHit.WebDAV.Client.Upload.UploadItem#OnProgressChanged
 * @property {ITHit.WebDAV.Client.Upload.UploadItem} Sender Upload item instance.
 * @property {string} Name Event name.
 * @property {ITHit.WebDAV.Client.Upload.Progress} OldProgress Previous progress.
 * @property {ITHit.WebDAV.Client.Upload.Progress} NewProgress Actual progress.
 * @example
 * /&#x002A&#x002A @typedef {ITHit.WebDAV.Client.Upload.UploadItem} oItem &#x002A/
 * var oItem = oUploader.Queue.GetByUrl(sSomeUrl);
 * oItem.AddListener('OnProgressChanged', function (oProgressChanged) {
 *         console.log('Upload to:' + oStateChanged.Sender.GetUrl() +  ', completed by:' + oProgressChanged.NewProgress.Completed + '%');
 *     });
 *
 */

/**
 * Event reporting that upload error occurred.
 * @api
 * @event ITHit.WebDAV.Client.Upload.UploadItem#OnError
 * @property {ITHit.WebDAV.Client.Upload.UploadItem} Sender Upload item instance.
 * @property {string} Name Event name.
 * @property {Error|ITHit.WebDAV.Client.Exceptions.WebDavException} Error.
 * @example
 * /&#x002A&#x002A @typedef {ITHit.WebDAV.Client.Upload.UploadItem} oItem &#x002A/
 * var oItem = oUploader.Queue.GetByUrl(sSomeUrl);
 * oItem.AddListener('OnError', function (oOnError) {
 *         console.log('Upload to:' + oOnError.Sender.GetUrl() +  ', failed with error:' + oOnError.Error.toString());
 *     });
 *
 */

/**
 * Event fired before {@link ITHit.WebDAV.Client.Upload.UploadItem} started upload.
 * @api
 * @event ITHit.WebDAV.Client.Upload.UploadItem#OnBeforeUploadStarted
 * @type {ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted}
 * You will validate item in this event and present user interface if user interaction is necessary.
 * In this event you can check if each item exists on the server and specify if item should be overwritten or skipped.
 * You can also validate file size, file extension, file upload path and file name.
 *
 * To continue upload the {@link ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted#Upload} function should be called.
 * To skip upload the {@link ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted#Skip} function should be called.
 * @api
 * @example
 * /&#x002A&#x002A @typedef {ITHit.WebDAV.Client.Upload.UploadItem} oItem &#x002A/
 * var oItem = oUploader.Queue.GetByUrl(sSomeUrl);
 * oItem.AddListener('OnBeforeUploadStarted', function(oBeforeUploadStarted) {
 *   WebDAVController.WebDavSession.OpenItemAsync(sHref,
 *       [],
 *       function(oAsyncResult) {
 *           if (oAsyncResult.IsSuccess) {
 *              oItem.SetSkip(true);
 *           }
 *
 *           oBeforeUploadStarted.Done();
 *       });
 * });
 */

/**
 * Event fired when is possible to retry failed upload and waited until one of action called.
 * @api
 * @event ITHit.WebDAV.Client.Upload.UploadItem#OnUploadError
 * @type {ITHit.WebDAV.Client.Upload.Events.UploadError}
 * @example
 * /&#x002A&#x002A @typedef {ITHit.WebDAV.Client.Upload.UploadItem} oItem &#x002A/
 * var oItem = oUploader.Queue.GetByUrl(sSomeUrl);
 * AddListener('OnUploadError', function(oUploadError) {
 *   setTimeout(function() {
 *    oUploadError.Retry();
 *  }, 2000)
 * });
 */

/**
 * Callback function to be called when action performed.
 * @api
 * @callback ITHit.WebDAV.Client.Upload.UploadItem~AsyncCallback
 */

(function() {
    'use strict';


    /**
     * Represents a file or folder being uploaded. Provides functions to discover item state, get info about upload
     * progress as well as to pause, resume and cancel upload.
     * @api
     * @class ITHit.WebDAV.Client.Upload.UploadItem
     * @param {string} sUrl
     * @param {ITHit.WebDAV.Client.Upload.FSEntry} oFsEntry
     * @param {ITHit.WebDAV.Client.Upload.Controls.HtmlControl} oBinding
     * @param {ITHit.WebDAV.Client.Upload.UploaderSession} oSession
     * @param {ITHit.WebDAV.Client.Upload.Groups.GroupManager} oGroupManager
     * @param {ITHit.WebDAV.Client.Upload.Settings} oSettings
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.UploadItem',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.UploadItem.prototype */ {

            /**
             * Gets [File]{@link https://www.w3.org/TR/FileAPI/} object. Returns null in case of a folder.
             * @api
             * @return {(File | null )}
             */
            GetFile: function() {
                return this._UploadProvider.FSEntry.GetFile();
            },

            /**
             * Get target url.
             * @api
             * @return {string} File or folder target upload URL.
             */
            GetUrl: function() {
                return this._UploadProvider.Url.GetHref();
            },

            /**
             * Get base url.
             * @return {string}
             */
            GetBaseUrl: function() {
                return this._UploadProvider.Url.GetBaseUrl();
            },

            /**
             * Gets file or folder name with extension.
             * @api
             * @return {string} File or folder name.
             */
            GetName: function() {
                return this._UploadProvider.Url.GetName();
            },

            /**
             * Gets relative path.
             * @api
             * @return {string} File or folder relative path.
             */
            GetRelativePath: function() {
                return this._UploadProvider.Url.GetRelativePath();
            },

            /**
             * Check if upload item represents a folder item.
             * @return {boolean} True if item is a folder. Otherwise - false.
             */
            IsFolder: function() {
                return this._UploadProvider.FSEntry.IsFolder();
            },

            /**
             * Get {@link ITHit.WebDAV.Client.Upload.Controls.HtmlControl} Where upload item created.
             * @return {ITHit.WebDAV.Client.Upload.Controls.HtmlControl}
             */
            GetSource: function() {
                return this._Source;
            },

            /**
             * Gets current upload state.
             * @api
             * @return {(ITHit.WebDAV.Client.Upload.State | string)}
             */
            GetState: function() {
                return this._UploadProvider.GetState().GetAsEnum();
            },

            /**
             * Gets object that describes upload progress.
             * @api
             * @return {ITHit.WebDAV.Client.Upload.Progress }
             */
            GetProgress: function() {
                return this._UploadProvider.GetProgress();
            },


            /**
             * Gets all upload errors.
             * @api
             * @return {(Error[]|ITHit.WebDAV.Client.Exceptions.WebDavException[])}
             */
            GetErrors: function() {
                return this._UploadProvider.Errors.slice();
            },

            /**
             * Gets last upload error.
             * @api
             * @return {(Error|ITHit.WebDAV.Client.Exceptions.WebDavException)}
             */
            GetLastError: function() {
                return this._UploadProvider.LastError;
            },

            /**
             * Callback function called before {@link ITHit.WebDAV.Client.Upload.UploadItem} started upload.
             * You will validate item in this event and present user interface if user interaction is necessary.
             * In this event you can check if each item exists on the server and specify if item should be overwritten or skipped.
             * You can also validate file size, file extension, file upload path and file name.
             *
             * To continue upload the {@link ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted#Upload} function should be called.
             * To skip upload the {@link ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted#Skip} function should be called.
             * @private
             * @callback ITHit.WebDAV.Client.Upload.UploadItem~OnUploadStartedCallback
             * @param {ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted} oEvent Event Object
             * @example
             * /&#x002A&#x002A @typedef {ITHit.WebDAV.Client.Upload.UploadItem} oItem &#x002A/
             * var oItem = oUploader.Queue.GetByUrl(sSomeUrl);
             * oItem.OnUploadStartedCallback = function (oOnBeforeUploadStart) {
             *   WebDAVController.WebDavSession.OpenItemAsync(sHref,
             *       [],
             *       function(oAsyncResult) {
             *           if (oAsyncResult.IsSuccess) {
             *              oItem.SetSkip(true);
             *           }
             *
             *           oBeforeUploadStart.Done();
             *       });
             * };
             */

            /**
             * Gets or Sets [OnUploadStartedCallback]{@link ITHit.WebDAV.Client.Upload.UploadItem~OnUploadStartedCallback} handler.
             * @private
             * @type {ITHit.WebDAV.Client.Upload.UploadItem~OnUploadStartedCallback}
             */
            OnUploadStartedCallback: null,

            /**
             * Callback function to be called when is possible to retry failed upload and waited until one of action called.
             * @private
             * @callback ITHit.WebDAV.Client.Upload.UploadItem~OnUploadErrorCallback
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadError} oEvent Event Object
             * @example
             * /&#x002A&#x002A @typedef {ITHit.WebDAV.Client.Upload.UploadItem} oItem &#x002A/
             * var oItem = oUploader.Queue.GetByUrl(sSomeUrl);
             * oItem.OnUploadErrorCallback = function (oOnUploadError) {
             *   setTimeout(function() {
             *    oUploadError.Retry();
             *  }, 2000)
             * };
             */

            /**
             * Gets or Sets [OnUploadErrorCallback]{@link ITHit.WebDAV.Client.Upload.UploadItem~OnUploadStartedCallback} handler.
             * @private
             * @type {ITHit.WebDAV.Client.Upload.UploadItem~OnUploadErrorCallback}
             */
            OnUploadErrorCallback: null,

            /**
             * Stores custom data.
             * @api
             * @type {Object}
             */
            CustomData: null,

            /**
             * Sets if the item is overwritten if it exists on the server. 
             * If false is passed and the file exists on the server upload will fail and the UploadItem will be set in the error state. Default is false.
             * @api
             * @param {boolean} Pass true to force the file to be overwritten. Pass false to make upload fail if file exists. 
             */
            SetOverwrite: function(bRewrite) {
               this._UploadProvider.Settings.ForceRewrite = bRewrite;
            },

            /**
             * Adds HTTP header to upload. Note that depending on your web server and web browser, 
             * maximum allowed request header size or size of all headers in total may be limited.
             * @api
             * @param {String} sName Header name.
             * @param {String} sValue Header value. 
             */
            AddHeader: function(sName, sValue) {                
                this._UploadProvider.Settings.CustomHeaders = this._UploadProvider.Settings.CustomHeaders || [];
                
                var existingHeader = ITHit.Utils.FindBy(this._UploadProvider.Settings.CustomHeaders,
                    function(headerElement) { 
                        return headerElement.name===sName; 
                    });

                if (existingHeader) {
                    existingHeader.value = sValue;
                } else {
                    this._UploadProvider.Settings.CustomHeaders.push({name: sName, value: sValue});
                }
            },

            SetRewrite: function(bRewrite){
                this.SetOverwrite(bRewrite);
            },

            /**
             * Gets if the item will be overwritten if it exists on the server.
             * @api
             * @return {boolean} True if the file on the server will be overwritten. Otherwise - false. Default is false.
             */
            GetOverwrite: function() {
                return this._UploadProvider.Settings.ForceRewrite;
            },

            GetRewrite: function() {
                return this.GetOverwrite();
            },

            /**
             * Sets if the file should be deleted if upload is canceled. 
             * By default, the file is deleted if the upload is canceled. To override this behavior, call this method passing false as a parameter. 
             * This function must be called on files only.
             * @api
             * @param {boolean} bDelete Specifies if the file should be deleted on cancel. Typically you will pass false if the file existed before upload. 
             * You will pass true to set the default behavior and delete the file when the upload is canceled.
             * @throws {ITHit.Exceptions.ArgumentException} Thrown if this function is called on folder item.
             */
            SetDeleteOnCancel: function(bDelete) {
                if(this.IsFolder() && bDelete === true) throw new ITHit.Exceptions.ArgumentException(null, 'bDelete');
                this._UploadProvider.Settings.DeleteOnCancel = bDelete;
            },

            /**
             * Gets if the file is deleted when the upload is canceled.
             * @api
             * @return {boolean} True if file is deleted when upload is canceled. Otherwise - false. Default is true.
             */
            GetDeleteOnCancel: function() {
                return this._UploadProvider.Settings.DeleteOnCancel;
            },

            /**
             * Sets skip state. Skipped items will not be added to the upload queue or automatically uploaded if they already in queue.
             */
            SetSkip: function() {
                this._UploadProvider.Skip();
            },

            /**
             * Sets failed state.
             * Populates item's error with provided error instance.
             * @api
             * @param {ITHit.WebDAV.Client.Exceptions.WebDavException} oError - The error instance that will be set as a failure description.
             * @throws {ITHit.Exceptions.ArgumentException} - Thrown if argument is not derived from {@link ITHit.WebDAV.Client.Exceptions.WebDavException}.
             * @example
             * var oUploader = new ITHit.WebDAV.Client.Upload.Uploader();
             * oUploader.Queue.OnUploadItemsCreated = function(oUploadItemsCreated) {
             *     var sErrorMessage = 'Added to queue in failed state';
             *      var oWebDavException = new ITHit.WebDAV.Client.Exceptions.WebDavException(sMessage);
             *
             *      /&#42;&#42; &#64;typedef {ITHit.WebDAV.Client.Upload.UploadItem[]} aItemsToUpload &#42;/
             *     oUploadItemsCreated.Items.forEach(function(oItem) {
             *         oItem.SetFailed(oWebDavException);
             *     }
             *
             *      oUploadItemsCreated.Upload(oUploadItemsCreated.Items);
             * });
             *
             */
            SetFailed: function(oError) {
                if (!(oError instanceof ITHit.WebDAV.Client.Exceptions.WebDavException)) {
                    var sMessage = ITHit.Phrases.WrongParameterType.Paste('ITHit.WebDAV.Client.Exceptions.WebDavException');
                    throw new ITHit.Exceptions.ArgumentException(sMessage, 'oError');
                }

                this._UploadProvider.SetFailed(oError);
            },

            /**
             * Set progress
             * @param {ITHit.WebDAV.Client.Upload.Events.ProgressChanged} oProgress The progress object to set.
             * @private
             */
            _SetProgress: function(oProgress) {
                var oEvent = new ITHit.WebDAV.Client.Upload.Events.ProgressChanged(this, oProgress.OldProgress, oProgress.NewProgress);
                ITHit.Events.DispatchEvent(this, oEvent.Name, oEvent);
            },

            /**
             * @type {ITHit.WebDAV.Client.Upload.Controls.HtmlControl}
             */
            _Source: null,

            /**
             * @type {ITHit.WebDAV.Client.Upload.Providers.UploadProvider}
             */
            _UploadProvider: null,


            constructor: function(sUrl, oFsEntry, oBinding, oSession, oGroupManager, oSettings) {
                this._Source = oBinding || null;
                this._GroupManager = oGroupManager;
                var oDavUrl = new ITHit.WebDAV.Client.Upload.Utils.DavUrl(
                    ITHit.WebDAV.Client.Encoder.Encode(oFsEntry.GetRelativePath()), 
                    sUrl);
                this._UploadProvider = new ITHit.WebDAV.Client.Upload.Providers.UploadProvider(oSession, this, oFsEntry, oDavUrl, oSettings);
                this._UploadProvider.AddListener('OnProgressChanged', this._SetProgress, this);
                this._UploadProvider.AddListener('OnStateChanged', this._OnStateChangedEventHandler, this);
                this._UploadProvider.AddListener('OnError', this._OnErrorEventHandler, this);
                this.CustomData = {};
            },

            /**
             * Begins upload.
             * @api
             * @param {ITHit.WebDAV.Client.Upload.UploadItem~AsyncCallback} [fCallback] The callback to call when upload is paused.
             */
            StartAsync: function(fCallback) {
                fCallback = fCallback || function() {};
                if (this.GetState() !== ITHit.WebDAV.Client.Upload.State.Paused) {
                    var that = this;
                    this._GetUploadBehaviourAsync(function() {
                        if (that.GetState() === ITHit.WebDAV.Client.Upload.State.Skipped) {
                            fCallback();
                        }
                        else {
                            that._UploadProvider.StartUploadAsync(fCallback);
                        }
                    });
                } else {
                    this._UploadProvider.StartUploadAsync(fCallback);
                }
            },

            /**
             * Pauses upload.
             * @api
             * @param {ITHit.WebDAV.Client.Upload.UploadItem~AsyncCallback} [fCallback] The callback to call when upload is paused.
             */
            PauseAsync: function(fCallback) {
                fCallback = fCallback || function() { };
                this._UploadProvider.PauseUpload(fCallback);
            },

            /**
             * Aborts upload.
             * @api
             * @param {number} [iTryCount] Number of times to try to delete the file if the file did not exist on the server before upload.
             * Pass 0 to not try to delete the file. Default is: 5.
             * @param {number} [iDelayAttempt] Delay between attempts to delete in milliseconds. Default is: 500.
             * @param {ITHit.WebDAV.Client.Upload.UploadItem~AsyncCallback} [fCallback] The callback to call when upload is cancelled.
             */
            CancelAsync: function(iTryCount, iDelayAttempt, fCallback) {
                fCallback = fCallback || function() { };
                iTryCount = iTryCount || 5;
                iDelayAttempt = iDelayAttempt || 500;
                this._UploadProvider.AbortUpload(iTryCount, iDelayAttempt, fCallback);
            },

            /**
             * Get File size.
             * @return {number} Size of the file.
             */
            GetSize: function() {
                return this._UploadProvider.FSEntry.GetSize();
            },

            /**
             * Dispatches event before upload start.
             * @private
             */
            _GetUploadBehaviourAsync: function(fCallback) {
                var oEvent = new ITHit.WebDAV.Client.Upload.Events.BeforeUploadStarted(this, fCallback);
                if (this.OnUploadStartedCallback) {
                    this.OnUploadStartedCallback(oEvent);
                } else if (ITHit.Events.ListenersLength(this, oEvent.Name) !== 0) {
                    ITHit.Events.DispatchEvent(this, oEvent.Name, oEvent);
                } else {
                    fCallback();
                }
            },

            /**
             * Add event handlers.
             * @api
             * @param {string} sEventName The event name to handle.
             * @param {Function} fCallback The callback to call.
             * @param {object} [oContext] The context to callback is called with.
             */
            AddListener: function(sEventName, fCallback, oContext) {
                this._ValidateEventName(sEventName);
                oContext = oContext || null;
                ITHit.Events.AddListener(this, sEventName, fCallback, oContext);
            },

            /**
             * Remove event listener.
             * @api
             * @param {string} sEventName The event name to remove.
             * @param {Function} fCallback The callback to call.
             * @param {object} [oContext] The context to callback is called with.
             */
            RemoveListener: function(sEventName, fCallback, oContext) {
                this._ValidateEventName(sEventName);
                oContext = oContext || null;
                ITHit.Events.RemoveListener(this, sEventName, fCallback, oContext);
            },

            /**
             * @param {string} sEventName
             * @private
             */
            _ValidateEventName: function(sEventName) {
                switch (sEventName) {
                    case ITHit.WebDAV.Client.Upload.Events.EventName.OnStateChanged:
                    case ITHit.WebDAV.Client.Upload.Events.EventName.OnProgressChanged:
                    case ITHit.WebDAV.Client.Upload.Events.EventName.OnError:
                    case ITHit.WebDAV.Client.Upload.Events.EventName.OnBeforeUploadStarted:
                    case ITHit.WebDAV.Client.Upload.Events.EventName.OnUploadError:
                        break;

                    default:
                        throw new ITHit.Exceptions.ArgumentException('Not found event name `' + sEventName + '`');
                }
            },


            /**
             * @public
             * @return ITHit.WebDAV.Client.Upload.Groups.GroupManager
             */
            GetGroup: function(){
                return this._GroupManager.GetGroupByItem(this);
            },

            /**
             * @private
             * @readonly
             * @type{ITHit.WebDAV.Client.Upload.Groups.GroupManager}
             */
            _GroupManager: null,

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Events.StateChanged} oEventData
             * @private
             */
            _OnStateChangedEventHandler: function(oEventData) {
                var oEvent = new ITHit.WebDAV.Client.Upload.Events.StateChanged(this, oEventData.OldState, oEventData.NewState);
                ITHit.Events.DispatchEvent(this, oEvent.Name, oEvent);
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Events.Error} oEventData
             * @private
             */
            _OnErrorEventHandler: function(oEventData) {
                var oEvent = new ITHit.WebDAV.Client.Upload.Events.Error(this, oEventData.Error);
                ITHit.Events.DispatchEvent(this, oEvent.Name, oEvent);
            }
        });
})();


(function() {
    'use strict';

    /**
     * @class ITHit.WebDAV.Client.Upload.Events.QueueChanged
     * @extends ITHit.WebDAV.Client.Upload.Events.BaseEvent
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Events.QueueChanged',
        ITHit.WebDAV.Client.Upload.Events.BaseEvent,
        /** @lends ITHit.WebDAV.Client.Upload.Events.QueueChanged.prototype */
        {

            /**
             * Added items.
             * @type {ITHit.WebDAV.Client.Upload.UploadItem[]}
             */
            AddedItems: [],

            /**
             * Removed items.
             * @type {ITHit.WebDAV.Client.Upload.UploadItem[]}
             */
            RemovedItems: [],

            constructor: function(oSender, aAdded, aRemoved) {
                this.Name = ITHit.WebDAV.Client.Upload.Events.EventName.OnQueueChanged;
                this.AddedItems = aAdded || [];
                this.RemovedItems = aRemoved || [];
                this.Sender = oSender;
            }

        });
})();

(function() {
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.FileSpan',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.FileSpan.prototype */
        {

            /**
             * Gets start of the span.
             * @public
             * @return {number}
             */
            GetStart: function() {
                return this._Start;
            },

            /**
             * Sets start of the span.
             * @public
             * @param {number} iStart
             */
            SetStart: function(iStart) {
                if (this._End && iStart > this._End) {
                    throw new ITHit.Exceptions.ArgumentException('Start cant be bigger than end', 'iStart');
                }

                this._Start = iStart;
            },

            /**
             * Gets end of the span. Match end of file if null.
             * @public
             * @return {number}
             */
            GetEnd: function() {
                return this._End;
            },

            /**
             * Sets end of the span. Match end of file if null.
             * @public
             * @param {(number | null)} iEnd
             */
            SetEnd: function(iEnd) {
                if (iEnd < this._Start) {
                    throw new ITHit.Exceptions.ArgumentException('End cant be smaller than start', 'iEnd');
                }
                
                this._End = iEnd || this._Blob.size;
            },

            /**
             * @private
             * @type {number}
             */
            _Start: 0,

            /**
             * @private
             * @type {(number | null)}
             */
            _End: 0,

            _Blob: null,

            /**
             * @alias ITHit.WebDAV.Client.Upload.FileSpan
             * @constructs
             * @public
             * @param {Blob} oFile
             * @param {number} [iStart]
             * @param {(number | null)} [iEnd]
             */
            constructor: function(oFile, iStart, iEnd) {
                this._SetBlob(oFile);
                this.SetStart(iStart);
                this.SetEnd(iEnd || oFile.size);
            },

            _SetBlob: function(oBlob){
                this._Blob = oBlob;
                this._Start = 0;
                this._End = oBlob.size;
            },

            /**
             * @return {boolean}
             */
            IsFullFile:function(){
                return this._Start === 0 && this._End === this._Blob.size;
            },

            /**
             * @return {boolean}
             */
            IsPartFile:function(){
                return !this.IsFullFile();
            },

            /**
             * @return {Blob}
             */
            GetSlice: function(){
                if (this.IsFullFile()) {
                    return this._Blob;
                }

                return this._Blob.slice(this._Start, this.End);
            },

            /**
             * @return {Blob}
             */
            GetFile: function(){
                return this._Blob;
            },

            /**
             * @return {number}
             */
            GetFullSize: function(){
                return this._Blob.size;
            }
        });
})();

(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.UploadLocation',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.UploadLocation.prototype */ {
            /**
             * @alias ITHit.WebDAV.Client.Upload.UploadLocation
             * @constructs
             * @param {ITHit.WebDAV.Client.Upload.Path.Generator} oGenerator
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             */
            constructor: function(oGenerator, oUrl) {
                this._FolderGenerator = oGenerator;
                this._Url = oUrl;
                this._PathMap = new ITHit.WebDAV.Client.Upload.Path.PathCache();
            },

            /**
             * @param {Function} fCallback
             * @param {Object} thisArg
             */
            CreateAsync: function(fCallback, thisArg) {
                var OnGeneratePathCompleted = function(oAsyncResult) {
                    delete this._CancellationCallback;
                    fCallback.call(thisArg, oAsyncResult);
                };
                this._CancellationCallback = this._FolderGenerator.GeneratePathAsync(this._PathMap, this._Url, OnGeneratePathCompleted, this);
            },


            IsExists: function() {
                return this._PathMap.Has(this._Url);
            },

            SetNotExists: function(){
                var aUrlList = this._GetAncestorsPaths(this._Url);
                aUrlList.forEach(function(oUrl) {
                    this._PathMap.Delete(oUrl);
                }, this);
            },

            /**
             * @return {boolean}
             */
            IsInProgress: function() {
                return !!this._CancellationCallback;
            },

            AbortRunningCreationAsync: function(fCallback, thisArg) {
                if (!this._CancellationCallback) {
                    fCallback.call(thisArg);
                    return;
                }

                this._CancellationCallback(function() {
                    fCallback.call(thisArg);
                }, this);
            },

            /**
             * @return {ITHit.WebDAV.Client.Upload.Path.PathCache}
             */
            GetCache: function() {
                return this._PathMap;
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Path.PathCache} oCache
             */
            SetCache: function(oCache){
                this._PathMap = oCache;
            },
            _CancellationCallback: null,
            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Path.Generator}
             */
            _FolderGenerator: null,
            /**
             * @public
             * @type {ITHit.WebDAV.Client.Upload.Path.PathCache}
             */
            _PathMap: null,
            /**
             * @type {ITHit.WebDAV.Client.Upload.Utils.DavUrl}
             */
            _Url: null,

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             * @return {ITHit.WebDAV.Client.Upload.Utils.DavUrl[]}
             */
            _GetAncestorsPaths: function(oUrl) {
                var parts = oUrl.GetRelativePath().split('/');

                if (parts.length === 0) return [];
                if (parts[parts.length - 1]==='') parts = parts.slice(0, -1);
                var aUrlToProcess = [];

                var path = '';
                for (var i = 0; i < parts.length - 1; i++) {
                    if (path !== '') path += '/';
                    path += parts[i];
                    aUrlToProcess.push(new ITHit.WebDAV.Client.Upload.Utils.DavUrl(path, oUrl.GetBaseUrl()));
                }

                return aUrlToProcess;
            }
        });
})();

(function() {
    'use strict';

    var self = ITHit.DefineClass('ITHit.WebDAV.Client.Upload.ContentWriter',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.ContentWriter.prototype */ {
            /**
             * Upload url.
             * @public
             * @readonly
             * @type {ITHit.WebDAV.Client.Upload.Utils.DavUrl}
             *
             */
            Url: null,

            /**
             * @alias ITHit.WebDAV.Client.Upload.ContentWriter
             * @constructs
             * @param {ITHit.WebDAV.Client.Upload.UploaderSession} oSession
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             */
            constructor: function(oSession, oUrl) {
                this._Session = oSession;
                this.Url = oUrl;
            },

            /**
             * @public
             * @param {number} iPeriod
             */
            SetProgressDebounce: function(iPeriod) {
                this._ReportPeriod = iPeriod;
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.FSEntry} oFsEntry
             */
            BeginWrite: function(oFsEntry) {
                this._InitializeRequestContext();
                var oWebDavRequest = null;
                if (oFsEntry.IsFolder()) {
                    oWebDavRequest = this._CreateMKCOLRequest();
                    this._AddCustomHeaders(oWebDavRequest);
                    this._RequestContext.AddListener('OnError', this._OnErrorEventHandler, this);
                    oWebDavRequest.GetResponse(this._OnResponse.bind(this));
                    this._RaiseOnStartEvent();
                    return;
                }

                oWebDavRequest = this._CreatePutRequest(oFsEntry);
                oWebDavRequest.Headers.Add('Overwrite', 'F');
                this._AddCustomHeaders(oWebDavRequest);
                this._RequestContext.AddListener('OnError', this._OnErrorEventHandler, this);
                oWebDavRequest.GetResponse(this._OnResponse.bind(this));
                this._RaiseOnStartEvent();
            },

            
            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.FSEntry} oFsEntry
             */
            BeginRewrite: function(oFsEntry) {
                this._InitializeRequestContext();
                var oWebDavRequest = null;
                if (oFsEntry.IsFolder()) {
                    oWebDavRequest = this._CreateMKCOLRequest();
                    this._AddCustomHeaders(oWebDavRequest);              
                    this._RequestContext.AddListener('OnError', this._OnMKCOLRewriteErrorEventHandler, this);
                    oWebDavRequest.GetResponse(this._OnMKCOLRewriteResponse.bind(this));
                    this._RaiseOnStartEvent();
                } else {
                    oWebDavRequest = this._CreatePutRequest(oFsEntry);
                    oWebDavRequest.Headers.Add('Overwrite', 'T');
                    this._AddCustomHeaders(oWebDavRequest);
                    this._RequestContext.AddListener('OnError', this._OnErrorEventHandler, this);
                    oWebDavRequest.GetResponse(this._OnResponse.bind(this));
                    this._RaiseOnStartEvent();
                }
            },


            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.FileSpan} oSpan
             */
            BeginAppend: function(oSpan) {
                this._InitializeRequestContext();
                var oWebDavRequest = this._CreatePutAppendRequest(oSpan);
                oWebDavRequest.Headers.Add('Overwrite', 'T');
                this._AddCustomHeaders(oWebDavRequest);
                this._RequestContext.AddListener('OnError', this._OnErrorEventHandler, this);
                oWebDavRequest.GetResponse(this._OnResponse.bind(this));
                this._RaiseOnStartEvent();
            },

            /**
             * @public
             * @param {Function} fCallback
             * @param {Object} thisArg
             */
            AbortAsync: function(fCallback, thisArg) {
                if (this._RequestContext) {
                    this._RequestContext.RemoveListener(ITHit.WebDAV.Client.Request.EVENT_ON_UPLOAD_PROGRESS, this._OnProgressEventHandler, this);
                    this._RequestContext.AbortAsync(fCallback, thisArg);
                }
            },

            /**
             * @public
             * @param {string} sEventName
             * @param {(function | string)} fCallback
             * @param {object} [oContext]
             */
            AddListener: function(sEventName, fCallback, oContext) {
                oContext = oContext || null;
                this._ValidateEventName(sEventName);
                ITHit.Events.AddListener(this, sEventName, fCallback, oContext);
            },

            /**
             * @public
             * @param {string} sEventName
             * @param {(function | string)} fCallback
             * @param {object} [oContext]
             */
            RemoveListener: function(sEventName, fCallback, oContext) {
                oContext = oContext || null;
                this._ValidateEventName(sEventName);
                ITHit.Events.RemoveListener(this, sEventName, fCallback, oContext);
            },

            /**
             * @param {WebDavRequest} oWebDavRequest
             * @private
             */
            _AddCustomHeaders: function(oWebDavRequest) {
                if (!this.CustomHeaders) return;
                var addedHeaders = [];
                var presentHeaders = oWebDavRequest.Headers.GetAll();

                this.CustomHeaders.forEach(function(headerItem) {
                    if (addedHeaders.indexOf(headerItem.name) < 0 && !presentHeaders.hasOwnProperty(headerItem.name)) {
                        oWebDavRequest.Headers.Add(headerItem.name,headerItem.value);
                        addedHeaders.push(headerItem.name);
                    }
                });
            },

            /**
             * @param {string} sEventName
             * @private
             */
            _ValidateEventName: function(sEventName) {
                switch (sEventName) {
                    case self.EVENT_ON_PROGRESS:
                    case self.EVENT_ON_ERROR:
                    case self.EVENT_ON_FINISH:
                    case self.EVENT_ON_START:
                        break;

                    default:
                        throw new ITHit.Exceptions.ArgumentException('Not found event name `' + sEventName + '`');
                }
            },

            /**
             * @protected
             */
            _InitializeRequestContext: function() {
                if (this.IsActive()) throw new ITHit.Exceptions('Content write already in progress');
                this._RequestContext = this._Session.CreateRequest(this.__className);
                this._RequestContext.AddListener(ITHit.WebDAV.Client.Request.EVENT_ON_UPLOAD_PROGRESS, this._OnProgressEventHandler, this);
            },

            /**
             * @private
             * @return {ITHit.WebDAV.Client.WebDavRequest}
             */
            _CreateMKCOLRequest: function() {
                var oWebDavRequest = this._RequestContext.CreateWebDavRequest(
                    ITHit.WebDAV.Client.Encoder.Encode(this.Url.GetOrigin()),
                    this.Url.GetHref()
                );

                oWebDavRequest.Method('MKCOL');
                this._SetDefaultHeaders(oWebDavRequest);
                return oWebDavRequest;
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.CancellableResult} oAsyncResult
             */
            _OnMKCOLRewriteResponse: function(oAsyncResult) {
                if (this._IsConflictResult(oAsyncResult)) {
                    oAsyncResult = this._TransformToSuccess(oAsyncResult);
                }
                this._OnResponse(oAsyncResult);
            },

            _OnMKCOLRewriteErrorEventHandler: function(oErrorEvent) {
                if (oErrorEvent.Error instanceof ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException) {
                    return;
                }
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.CancellableResult} oAsyncResult
             */
            _OnResponse: function(oAsyncResult) {
                if (oAsyncResult.IsAborted) {
                    oAsyncResult = ITHit.WebDAV.Client.CancellableResult.CreateAbortedResult(oAsyncResult.Error);
                    this._RequestContext.MarkAbort();
                } else {
                    oAsyncResult = ITHit.WebDAV.Client.CancellableResult.CreateFromAsyncResultResult(oAsyncResult);
                    this._RequestContext.MarkFinish();
                }

                this._RaiseOnFinishEvent(oAsyncResult);
                this._RemoveRequestContextEventListeners();
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.Upload.FSEntry} oFsEntry
             * @return {ITHit.WebDAV.Client.WebDavRequest}
             */
            _CreatePutRequest: function(oFsEntry) {
                var oWebDavRequest = this._RequestContext.CreateWebDavRequest(
                    ITHit.WebDAV.Client.Encoder.Encode(this.Url.GetOrigin()),
                    this.Url.GetHref()
                );

                oWebDavRequest.Method('PUT');

                // Add headers.
                if (oFsEntry.GetFile().type) {
                    oWebDavRequest.Headers.Add('Content-Type', oFsEntry.GetFile().type);
                }

                oWebDavRequest.BodyBinary(oFsEntry.GetFile());
                this._SetDefaultHeaders(oWebDavRequest);
                return oWebDavRequest;
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.Upload.FileSpan} oSpan
             * @return {ITHit.WebDAV.Client.WebDavRequest}
             */
            _CreatePutAppendRequest: function(oSpan) {
                var oWebDavRequest = this._RequestContext.CreateWebDavRequest(
                    ITHit.WebDAV.Client.Encoder.Encode(this.Url.GetOrigin()),
                    this.Url.GetHref()
                );

                oWebDavRequest.Method('PUT');

                // Add headers.
                if (oSpan.GetFile().type) {
                    oWebDavRequest.Headers.Add('Content-Type', oSpan.GetFile().type);
                }

                if (oSpan.IsPartFile()) {
                    oWebDavRequest.Headers.Add('Content-Range', this._GetRangeHeader(oSpan));
                    oWebDavRequest.BodyBinary(oSpan.GetSlice());
                } else {
                    oWebDavRequest.BodyBinary(oSpan.GetFile());
                }
                this._SetDefaultHeaders(oWebDavRequest);
                return oWebDavRequest;
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.FileSpan} oFileSpan
             * @private
             * @return {string}
             */
            _GetRangeHeader: function(oFileSpan) {
                return 'bytes ' + oFileSpan.GetStart() + '-' + (oFileSpan.GetEnd() - 1) + '/' + oFileSpan.GetFullSize();
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.AsyncResult} oAsyncResult
             * @return {ITHit.WebDAV.Client.AsyncResult}
             */
            _TransformToSuccess: function(oAsyncResult) {
                return new ITHit.WebDAV.Client.AsyncResult(oAsyncResult.Error, true, null);
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.AsyncResult} oAsyncResult
             * @return {boolean}
             */
            _IsConflictResult: function(oAsyncResult) {
                return oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException;
            },


            /**
             *
             * @protected
             * @param {ITHit.WebDAV.Client.RequestProgress} oProgressData
             */
            _RaiseOnProgressEvent: function(oProgressData) {
                ITHit.Events.DispatchEvent(this, self.EVENT_ON_PROGRESS, [{Progress: oProgressData, Uploader: this}]);
            },

            /**
             * @protected
             * @param {Error|ITHit.WebDAV.Client.Exceptions.WebDavException} oError
             */
            _RaiseOnErrorEvent: function(oError) {
                ITHit.Events.DispatchEvent(this, self.EVENT_ON_ERROR, [{Error: oError, Uploader: this}]);
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.AsyncResult} [oResult]
             */
            _RaiseOnFinishEvent: function(oResult) {
                ITHit.Events.DispatchEvent(this, self.EVENT_ON_FINISH, [{Uploader: this, Result: oResult}]);
            },

            /**
             * @private
             */
            _RaiseOnStartEvent: function() {
                ITHit.Events.DispatchEvent(this, self.EVENT_ON_START, [{Uploader: this}]);
            },

            /**
             * @protected
             * @param {ITHit.WebDAV.Client.Request#event:OnProgress} oProgressEvent
             */
            _OnProgressEventHandler: function(oProgressEvent) {
                var iNow = new Date().getTime();
                if (iNow - this._LastReportTime > this._ReportPeriod || oProgressEvent.Progress.BytesTotal === oProgressEvent.Progress.BytesLoaded) {
                    this._RaiseOnProgressEvent(oProgressEvent.Progress);
                    this._LastReportTime = iNow;
                }
            },

            /**
             * @protected
             * @param {ITHit.WebDAV.Client.Request#event:OnError} oErrorEvent
             */
            _OnErrorEventHandler: function(oErrorEvent) {
                this._RaiseOnErrorEvent(oErrorEvent.Error);
            },

            _RemoveRequestContextEventListeners: function() {
                ITHit.Events.RemoveAllListeners(this._RequestContext, 'OnUploadProgress');
                ITHit.Events.RemoveAllListeners(this._RequestContext, 'OnError');
                delete this._RequestContext;
            },

            /**
             * @protected
             * @param {ITHit.WebDAV.Client.WebDavRequest} oWebDavRequest
             */
            _SetDefaultHeaders: function(oWebDavRequest) {
                oWebDavRequest.Headers.Add('If-Modified-Since', 'Mon, 26 Jul 1997 05:00:00 GMT');
                oWebDavRequest.Headers.Add('X-Requested-With', 'XMLHttpRequest');
            },

            /**
             * @return {boolean}
             */
            IsActive: function() {
                return !!this._RequestContext;
            },


            /**
             * @protected
             * @type {ITHit.WebDAV.Client.Upload.UploaderSession}
             */
            _Session: null,

            /**
             * @protected
             * @type {ITHit.WebDAV.Client.Request}
             */
            _RequestContext: null,

            /**
             * Min time between progress reports.
             * @type {number}
             * @private
             * @readonly
             */
            _ReportPeriod: 1000,

            /**
             * Time of last progress event fired.
             * @private
             * @type {number}
             */
            _LastReportTime: 0
        },
        /** @lends ITHit.WebDAV.Client.Upload.ContentWriter */{

            /**
             * Progress event trigger on update information about request progress.
             * @public
             * @event ITHit.WebDAV.Client.Upload.ContentWriter#OnProgress
             * @property {ITHit.WebDAV.Client.RequestProgress} Progress Progress info instance
             * @property {ITHit.WebDAV.Client.Upload.ContentWriter} Uploader Current uploader
             */

            /** @constant
             *@type {string}
             *@default
             */
            EVENT_ON_PROGRESS: 'OnProgress',

            /**
             * Error event trigger when one of request operations have error.
             * Notice: This event trigger before async method callback.
             * @public
             * @event ITHit.WebDAV.Client.Upload.ContentWriter#OnError
             * @property {Error|ITHit.WebDAV.Client.Exceptions.WebDavException} Error Error object
             * @property {ITHit.WebDAV.Client.CancellableResult} Uploader Current uploader
             */

            /** @constant
             *@type {string}
             *@default
             */
            EVENT_ON_ERROR: 'OnError',

            /**
             * Finish event trigger once when all operations in requests is complete.
             * Notice: This event trigger before async method callback.
             * @public
             * @event ITHit.WebDAV.Client.Upload.ContentWriter#OnFinish
             * @property {ITHit.WebDAV.Client.Upload.ContentWriter} Uploader Current uploader
             * @property {ITHit.WebDAV.Client.CancellableResult} Result The result of upload
             */

            /** @constant
             *@type {string}
             *@default
             */
            EVENT_ON_FINISH: 'OnFinish',

            /**
             * Start event trigger once when operations request send.
             * Notice: This event trigger before async method callback.
             * @public
             * @event ITHit.WebDAV.Client.Upload.ContentWriter#OnStart
             * @property {ITHit.WebDAV.Client.Upload.ContentWriter} Uploader Current uploader
             */


            /** @constant
             *@type {string}
             *@default
             */
            EVENT_ON_START: 'OnStart'
        });
})();


(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Path.Generator',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Path.Generator.prototype */ {

            /**
             * @alias ITHit.WebDAV.Client.Upload.Path.Generator
             * @constructs
             * @param {ITHit.WebDAV.Client.Upload.UploaderSession} oSession
             */
            constructor: function(oSession){
                this._Session = oSession;
                this._WorkList = new ITHit.WebDAV.Client.Upload.Collections.Map();
            },

            /**
             *
             * @param oUrl
             * @return {ITHit.WebDAV.Client.Request}
             * @private
             */
            _SendRequest: function(oUrl) {
                var oRequest = this._Session.CreateRequest(this.__className + '.GeneratePathAsync()');
                ITHit.WebDAV.Client.Methods.Mkcol.GoAsync(
                    oRequest,
                    oUrl.toString(),
                    [],
                    ITHit.WebDAV.Client.Encoder.Encode(oUrl.GetHost()),
                    function(oAsyncResult) {
                        if (oAsyncResult.IsAborted) {
                            oRequest.MarkAbort();
                        } else {
                            oRequest.MarkFinish();
                        }
                        this._CallAwaiters(oUrl, oAsyncResult);
                    }.bind(this)
                );

                return oRequest;
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Path.PathCache} oCache
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl[]} aUrlList
             * @param {function} fCallback
             * @param {Object} thisArg
             * @return {ITHit.WebDAV.Client.Upload.Path.Generator~CancelCallback}
             * @private
             */
            _RecurrentGenerate: function(oCache, aUrlList, fCallback, thisArg) {

                var currentRequest = null;
                var nestedCancellation = null;
                var fCancelCallback = function(fCaller, oContext) {
                    if (!!currentRequest) {
                        currentRequest.AbortAsync(fCaller, oContext);
                        return;
                    }
                    
                    if (!!nestedCancellation) {
                        nestedCancellation(fCaller, oContext);
                    }

                    fCaller.call(thisArg);
                };

                var aWorkUrl = aUrlList.slice();
                var aResult = [];
                while (aWorkUrl.length > 0) {
                    var oUrl = aWorkUrl[0];
                    if (!oCache.Has(oUrl)) {
                        break;
                    }

                    aResult.push(oUrl);
                    aWorkUrl.splice(0, 1);
                }

                if (aWorkUrl.length === 0) {
                    fCallback.call(thisArg, ITHit.WebDAV.Client.CancellableResult.CreateSuccessfulResult(aResult));
                    return fCancelCallback;
                }
                var oFirstUrl = aWorkUrl.shift();

                if (!this._IsInWork(oFirstUrl)) {
                    currentRequest = this._SendRequest(oFirstUrl);
                }
                this._AddAwaiter(oFirstUrl, function(oAsyncResult) {
                    if (!oAsyncResult.IsSuccess && !this._IsConflictResult(oAsyncResult)) {
                        fCallback.call(thisArg, oAsyncResult);
                        return;
                    }

                    oCache.Add(oFirstUrl);
                    aResult.push(oUrl);
                    currentRequest = null;
                    nestedCancellation = this._RecurrentGenerate(oCache, aWorkUrl, function(oResult) {
                        if (oResult.IsSuccess || this._IsConflictResult(oAsyncResult)) {
                            oResult.Result.concat(aResult);
                            oResult = ITHit.WebDAV.Client.CancellableResult.CreateSuccessfulResult(aResult);
                        }
                        nestedCancellation = null;
                        fCallback.call(thisArg, oResult);
                        return;
                    }, this);
                }.bind(this));

                return fCancelCallback;
            },
            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Path.PathCache} oCache
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             * @param {function} fCallback
             * @param {Object} thisArg
             * @return {ITHit.WebDAV.Client.Upload.Path.Generator~CancelCallback}
             */
            GeneratePathAsync: function(oCache, oUrl, fCallback, thisArg){
                var aUrlList = this._GetAncestorsPaths(oUrl);
                if (aUrlList.length ===0) {
                    return fCallback.call(thisArg, ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult([]));
                }

                return this._RecurrentGenerate(oCache, aUrlList, fCallback, thisArg);
            },

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.UploaderSession}
             */
            _Session: null,
            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Collections.Map<Function[]>}
             */
            _WorkList: null,

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             * @return {ITHit.WebDAV.Client.Upload.Utils.DavUrl[]}
             */
            _GetAncestorsPaths: function(oUrl) {
                var parts = oUrl.GetRelativePath().split('/');

                if (parts.length === 0) return [];
                if (parts[parts.length - 1]==='') parts = parts.slice(0, -1);
                var aUrlToProcess = [];

                var path = '';
                for (var i = 0; i < parts.length - 1; i++) {
                    if (path !== '') path += '/';
                    path += parts[i];
                    aUrlToProcess.push(new ITHit.WebDAV.Client.Upload.Utils.DavUrl(path, oUrl.GetBaseUrl()));
                }

                return aUrlToProcess;
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             * @return {boolean}
             * @private
             */
            _IsInWork: function(oUrl) {
                var aWaiters = this._WorkList.Get(oUrl.toString());
                return aWaiters && (aWaiters.length > 0);
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             * @param {function} fCallback
             * @private
             */
            _AddAwaiter: function(oUrl, fCallback) {
                var aWaiters = this._WorkList.Get(oUrl.toString());
                var aNewAwaiters = [];
                if (aWaiters) {
                    aNewAwaiters = aNewAwaiters.concat(aWaiters);
                }

                aNewAwaiters.push(fCallback);
                this._WorkList.Set(oUrl.toString(), aNewAwaiters);
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             * @param {ITHit.WebDAV.Client.AsyncResult} oAsyncResult
             * @private
             */
            _CallAwaiters: function(oUrl, oAsyncResult) {
                var aWaiters = this._WorkList.Get(oUrl.toString());
                this._WorkList.Delete(oUrl.toString());
                aWaiters.forEach(function(fAwaiter) {
                    fAwaiter(oAsyncResult);
                });
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.AsyncResult} oAsyncResult
             * @private
             * @return {boolean}
             */
            _IsConflictResult: function(oAsyncResult) {
                if (oAsyncResult.IsSuccess) return false;
                if (oAsyncResult.Error && oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException){
                    return true;
                }

                return false;
            }
        });
})();

/**
 * @callback ITHit.WebDAV.Client.Upload.Path.Generator~CancelCallback
 * @param {Function} fCallback
 * @param {Object} [thisArg]
 */

(function() {
    /**
     * @public
     * @class ITHit.WebDAV.Client.Upload.UploaderSession
     * @extends ITHit.WebDAV.Client.WebDavSession
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.UploaderSession',
        ITHit.WebDAV.Client.WebDavSession,
        /** @lends ITHit.WebDAV.Client.Upload.UploaderSession.prototype */{


            ExistsFolders: [],

            /**
             * Callback function to be called when progress report loaded from server.
             * @callback ITHit.WebDAV.Client.UploaderSession~GetProgressReportAsyncCallback
             * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
             * @param {ITHit.WebDAV.Client.UploadProgressInfo[]} oResult.Result Progress report collection.
             */

            /**
             * Returns progress report corresponding to path.
             * @public
             * @param {string} sUrl The url to resource.
             * @param {ITHit.WebDAV.Client.UploaderSession~GetProgressReportAsyncCallback} fCallback
             * @param {Object} [thisArg]
             * @return {* | ITHit.WebDAV.Client.Request} Request object.
             */
            GetProgressReportAsync: function(sUrl, fCallback, thisArg) {
                var oRequest = this.CreateRequest(this.__className +

                    '.ReportAsync()');
                var sHref = ITHit.WebDAV.Client.Encoder.Encode(sUrl);
                var sHost = ITHit.WebDAV.Client.HierarchyItem.GetHost(sHref);
                ITHit.WebDAV.Client.Methods.Report.GoAsync(oRequest, sHref, sHost, null, null, function(oAsyncResult) {
                    oRequest.MarkFinish();
                    fCallback.call(thisArg, oAsyncResult);
                });

                return oRequest;
            },

            /**
             * Callback function to be called when upload cancelled on server.
             * @callback ITHit.WebDAV.Client.UploaderSession~CancelUploadAsyncCallback
             * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
             */

            /**
             * Cancels upload of resource corresponding to path. Works only with ITHit WebDAV DeltaV ReusableUpload Server.
             * @param {string} sUrl The url to resource.
             * @param {ITHit.WebDAV.Client.UploaderSession~CancelUploadAsyncCallback} fCallback
             * @return {ITHit.WebDAV.Client.Request} Request object.
             */
            CancelUploadAsync: function(sUrl, fCallback) {
                var oRequest = this.CreateRequest(this.__className +
                    '.CancelUpload()');
                var sHref = ITHit.WebDAV.Client.Encoder.Encode(sUrl);
                var sHost = ITHit.WebDAV.Client.HierarchyItem.GetHost(sHref);
                ITHit.WebDAV.Client.Methods.CancelUpload.GoAsync(oRequest, sHref, [], sHost, function(oAsyncResult) {
                    oRequest.MarkFinish();
                    var oUploadCancelResult = new ITHit.WebDAV.Client.AsyncResult(true, true, null);
                    if (oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.NotFoundException) {
                        oUploadCancelResult = new ITHit.WebDAV.Client.AsyncResult(true, true, null);
                    } else if (!oAsyncResult.IsSuccess) {
                        oUploadCancelResult = new ITHit.WebDAV.Client.AsyncResult(oAsyncResult.IsSuccess, oAsyncResult.IsSuccess, oAsyncResult.Error);
                    }

                    fCallback(oUploadCancelResult);
                });

                return oRequest;
            },

            /**
             * Callback function to be called when resource checked on server.
             * @callback ITHit.WebDAV.Client.UploaderSession~CheckExistsAsyncCallback
             * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
             * @param {boolean} oResult.Result True if exists; otherwise false.
             */


            /**
             * Checks if resource corresponding to path exists.
             * @param {string} sUrl The url to resource.
             * @param {ITHit.WebDAV.Client.UploaderSession~CheckExistsAsyncCallback} fCallback
             * @return {*} Request object.
             * @param {Object} thisArg
             */
            CheckExistsAsync: function(sUrl, fCallback, thisArg) {
                fCallback = fCallback || function() {};
                return this.OpenItemAsync(ITHit.WebDAV.Client.Encoder.Encode(sUrl),
                    [],
                    function(oAsyncResult) {
                        /** @type {ITHit.WebDAV.Client.AsyncResult} */
                        var oItemExistsResult = new ITHit.WebDAV.Client.AsyncResult(true, true, null);
                        if (oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.NotFoundException) {
                            oItemExistsResult = new ITHit.WebDAV.Client.AsyncResult(false, true, null);
                        } else if (!oAsyncResult.IsSuccess) {
                            oItemExistsResult = new ITHit.WebDAV.Client.AsyncResult(oAsyncResult.IsSuccess, oAsyncResult.IsSuccess, oAsyncResult.Error);
                        }

                        fCallback.call(thisArg, oItemExistsResult);
                    });
            },

            DeleteAsync: function(sPath, oLockTokens, fCallback) {
                oLockTokens = oLockTokens || null;
                var sHref = ITHit.WebDAV.Client.Encoder.Encode(sPath);
                var sHost = ITHit.WebDAV.Client.HierarchyItem.GetHost(sHref);
                var oRequest = this.CreateRequest(this.__className + '.DeleteAsync()');
                ITHit.WebDAV.Client.Methods.Delete.GoAsync(oRequest, sHref, oLockTokens, sHost, function(oAsyncResult) {
                    if(!oAsyncResult.IsSuccess && oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.NotFoundException) {
                        oAsyncResult = new ITHit.WebDAV.Client.AsyncResult(true, true, null);
                    }
                    oRequest.MarkFinish();
                    fCallback(oAsyncResult);
                });

                return oRequest;
            },


            /**
             * Callback function to be called when resource checked on server.
             * @callback ITHit.WebDAV.Client.UploaderSession~CreateFolderRangeAsyncCallback
             * @param {ITHit.WebDAV.Client.AsyncResult} oResult Result object
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl[]} oResult.Result
             */

            /**
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl[]} aPath
             * @param {(string|ITHit.WebDAV.Client.LockUriTokenPair)} oLockTokens
             * @param {Function} fCallback
             * @param {Object} thisArg
             * @return {*|ITHit.WebDAV.Client.Request}
             */
            CreateFolderRangeAsync: function(aPath, oLockTokens, fCallback, thisArg) {
                oLockTokens = oLockTokens || null;
                fCallback = fCallback || ITHit.Utils.NoOp;
                var iRequestsCount = aPath.length;
                var oRequest = this.CreateRequest(this.__className + '.CreateFolderRangeAsync()', iRequestsCount);
                this._PerformCreateFolderRangeMethodAsync(oRequest, aPath, oLockTokens, function(oAsyncResult) {
                    oRequest.MarkFinish();
                    fCallback.call(thisArg, oAsyncResult);
                });

                return oRequest;
            },


            /**
             * @param {ITHit.WebDAV.Client.Request} oRequest
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl[]} aPath
             * @param {(string|ITHit.WebDAV.Client.LockUriTokenPair)} oLockTokens
             * @param {ITHit.WebDAV.Client.UploaderSession~CreateFolderRangeAsyncCallback} [fCallback]
             * @param {Object} [thisArg]
             */
            _PerformCreateFolderRangeMethodAsync: function(oRequest, aPath, oLockTokens, fCallback, thisArg) {
                fCallback = fCallback || ITHit.Utils.NoOp;
                aPath = aPath.slice();
                var oCurrentUrl = aPath.unshift();
                var sHref = ITHit.WebDAV.Client.Encoder.Encode(oCurrentUrl.GetHref());
                var sHost = ITHit.WebDAV.Client.Encoder.Encode(oCurrentUrl.GetHost());
                ITHit.WebDAV.Client.Methods.Mkcol.GoAsync(oRequest, sHref, oLockTokens, sHost, function(oAsyncResult) {
                    if(oAsyncResult.IsSuccess || oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException) {
                     oAsyncResult = new ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult([oCurrentUrl]);
                    }

                    if (aPath.length > 0 && oAsyncResult.IsSuccess) {
                        this._PerformCreateFolderRangeMethodAsync(oRequest, aPath, oLockTokens, function(oAsyncResult) {
                            if (oAsyncResult.IsSuccess ) {
                                oAsyncResult.Result.push(oCurrentUrl);
                            }
                            fCallback.call(thisArg, oAsyncResult);
                            return;
                        }, this);
                    }
                    else {
                        fCallback.call(thisArg, oAsyncResult);
                        return;
                    }
                });
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             * @return {ITHit.WebDAV.Client.Upload.UploadLocation}
             */
            CreateUploadLocation: function(oUrl){
                return new ITHit.WebDAV.Client.Upload.UploadLocation(this.GetPathGenerator(), oUrl);
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             * @return {ITHit.WebDAV.Client.Upload.ContentWriter}
             */
            CreateContentWriter: function(oUrl){
                return new ITHit.WebDAV.Client.Upload.ContentWriter(this, oUrl);
            },

            /**
             * @return {ITHit.WebDAV.Client.Upload.Path.Generator}
             */
            GetPathGenerator: function(){
                if (!this._PathGenerator) this._PathGenerator = new ITHit.WebDAV.Client.Upload.Path.Generator(this);
                return this._PathGenerator;
            },

            /**
             * @type {ITHit.WebDAV.Client.Upload.Path.Generator}
             */
            _PathGenerator: null

        });
})();

(function() {
    'use strict';

    /**
     * Callback function to be called when task ends.
     * @public
     * @callback ITHit.WebDAV.Client.Upload.Utils.RepeatableActionContext~AfterAction
     * @extends Function
     * @template T
     * @param {T} Result
     */

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Utils.RepeatableActionContext',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Utils.RepeatableActionContext.prototype */
        {

            /**
             * @private
             * @type {number}
             */
            _RoundsCount: 0,

            /**
             * @private
             * @type {boolean}
             */
            _IsActive: true,

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Utils.RepeatableAction~Action<T>}
             */
            _Handler: null,

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Utils.RepeatableActionContext~AfterAction<T>}
             */
            _EndHandler: null,

            /**
             * @private
             * @type {number}
             */
            _RepeatTime: 0,

            /**
             * @class ITHit.WebDAV.Client.Upload.Utils.RepeatableActionContext
             * @constructs
             * Create new context.
             * @template T
             * @param {number} iDigestRounds
             * @param {number} iRepeatTime
             * @param {ITHit.WebDAV.Client.Upload.Utils.RepeatableAction~Action<T>} fHandler
             * @param {ITHit.WebDAV.Client.Upload.Utils.RepeatableActionContext~AfterAction<T>} fEndHandler
             */
            constructor: function(iDigestRounds, iRepeatTime, fHandler, fEndHandler) {
                this._RoundsCount = iDigestRounds;
                this._Handler = fHandler;
                this._EndHandler = fEndHandler;
                this._IsActive = !!iDigestRounds;
                this._RepeatTime = iRepeatTime;
            },

            /**
             * Stops action repeating with result.
             * @public
             * @param {T} [oResult]
             */
            Stop: function(oResult) {
                this._IsActive = false;
                this._RoundsCount = 0;
                this._EndHandler(oResult);
            },

            /**
             * Run next action digest.
             * @private
             */
            _RunRound: function() {
                if (this._IsActive) {
                    this._Handler(this);
                } else {
                    this.Stop();
                }
            },

            /**
             * End current
             * @param {T} [oResult]
             */
            EndRound: function(oResult) {
                this._RoundsCount--;
                if (this._RoundsCount === 0) {
                    this.Stop(oResult);
                } else {
                    setTimeout(this._RunRound.bind(this), this._RepeatTime);
                }
            }
        });
})();


/**
 * Callback function to be called when action performed.
 * @public
 * @callback ITHit.WebDAV.Client.Upload.Utils.RepeatableAction~Action
 * @template T
 * @param {ITHit.WebDAV.Client.Upload.Utils.RepeatableActionContext<T>} Context
 */

(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Utils.RepeatableAction',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Utils.RepeatableAction.prototype */
        {

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Utils.RepeatableAction~Action<T>}
             */
            _Action: null,

            /**
             * Created new task.
             * @public
             * @constructs
             * @param {ITHit.WebDAV.Client.Upload.Utils.RepeatableAction~Action<T>} fAction
             * @class ITHit.WebDAV.Client.Upload.Utils.RepeatableAction
             * @classdesc This class wraps action and perform repeating execution.
             * @template T
             */
            constructor: function(fAction) {
                this._Action = fAction;
            },

            /**
             * Runs action
             * @public
             * @param {number} RepeatCount
             * @param {number} RepeatTime
             * @param {ITHit.WebDAV.Client.Upload.Utils.RepeatableActionContext~AfterAction<T>} fContinue
             */
            RunAsync: function(RepeatCount, RepeatTime, fContinue) {
                /** @type {ITHit.WebDAV.Client.Upload.Utils.RepeatableActionContext<T>} */
                var oContext = new ITHit.WebDAV.Client.Upload.Utils.RepeatableActionContext(RepeatCount, RepeatTime, this._Action, fContinue);
                oContext._RunRound();
            }
        });
})();


(function() {
    'use strict';

    var self = ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Events.UploadError',
        ITHit.WebDAV.Client.Upload.Events.AsyncEvent,
        /** @lends ITHit.WebDAV.Client.Upload.Events.UploadError.prototype */
        {

            /**
             * Error object.
             * @api
             * @type {Error|ITHit.WebDAV.Client.Exceptions.WebDavException}
             */
            Error: null,


            /**
             * Skips retry. UploadItem becomes failed.
             * @api
             */
            Skip: function() {
                if (this._IsHandled) return;
                this._SkipRetry(this.Items);
            },

            /**
             * Retry upload.
             * @api
             */
            Retry: function() {
                if (this._IsHandled) return;
                this._Retry(this.Items);
            },


            /**
             * @api
             * @alias ITHit.WebDAV.Client.Upload.Events.UploadError
             * @extends ITHit.WebDAV.Client.Upload.Events.AsyncEvent
             * @constructs
             * @param {ITHit.WebDAV.Client.Upload.UploadItem} oSender
             * @param oError
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadError~ResultCallback} fCallback
             */
            constructor: function(oSender, oError, fCallback) {
                this.Name = ITHit.WebDAV.Client.Upload.Events.EventName.OnUploadError;
                this.Error = oError;
                this._super(oSender, fCallback);
            },

            /**
             *
             * @private
             */
            _Retry: function() {
                this._Handle(self.GetRetryResult(this.Error));
            },

            /**
             *
             * @private
             */
            _SkipRetry: function() {
                this._Handle(self.GetSkipResult(this.Error));
            }

        },
        /** @lends ITHit.WebDAV.Client.Upload.Events.UploadError */
        {
            /**
             *
             * @param {Error|ITHit.WebDAV.Client.Exceptions.WebDavException} oError
             * @return {ITHit.WebDAV.Client.Upload.Events.UploadError~Result}
             */
            GetSkipResult: function(oError) {
                return {Action: 'skip', Error: oError};
            },

            /**
             *
             * @param {Error|ITHit.WebDAV.Client.Exceptions.WebDavException} oError
             * @return {ITHit.WebDAV.Client.Upload.Events.UploadError~Result}
             */
            GetRetryResult: function(oError) {
                return {Action: 'retry', Error: oError};
            }
        });
})();

/**
 * @private
 * @typedef {Object} ITHit.WebDAV.Client.Upload.Events.UploadError~Result
 * @property {string} Action
 * @property Error|ITHit.WebDAV.Client.Exceptions.WebDavException} Error
 */


/**
 * @private
 * @callback ITHit.WebDAV.Client.Upload.Events.UploadError~ResultCallback
 * @param {string} oResult
 */

(function() {
    /**
     * This class provides state change event data;
     * @public
     * @class ITHit.WebDAV.Client.Upload.Events.Error
     * @extends ITHit.WebDAV.Client.Upload.Events.BaseEvent
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Events.Error',
        ITHit.WebDAV.Client.Upload.Events.BaseEvent,
        /** @lends ITHit.WebDAV.Client.Upload.Events.Error.prototype */
        {
            /**
             * Error object.
             * @public
             * @type {Error|ITHit.WebDAV.Client.Exceptions.WebDavException}
             */
            Error: null,

            constructor: function(oSender, oError) {
                this.Name = ITHit.WebDAV.Client.Upload.Events.EventName.OnError;
                this.Error = oError;
                this.Sender = oSender;
            }
        });
})();


(function() {
    'use strict';

    /**
     * @class ITHit.WebDAV.Client.Upload.States.BaseState
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.States.BaseState',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.States.BaseState.prototype */ {


            /**
             * Method called when context entering this state.
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             */
            OnEnter: function(oContext) {
            },

            /**
             * Method called when context leaving this state.
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             */
            OnLeave: function(oContext) {
            },
            /**
             * @public
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             * @param {Function} fCallback
             */
            StartUploadAsync: function(oContext, fCallback) {
                fCallback();
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             * @param {Function} fCallback
             */
            PauseUpload: function(oContext, fCallback) {
                fCallback();
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             * @param {number} iTryCount
             * @param {number} iRepeatTime
             * @param {Function} fCallback
             */
            AbortUpload: function(oContext, iTryCount, iRepeatTime, fCallback) {
                fCallback();
            },

            /**
             *
             * {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             */
            Skip: function(oContext) {
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             * @param {ITHit.WebDAV.Client.CancellableResult} oAsyncResult
             */
            OnUploadLocationPrepared: function(oContext, oAsyncResult) {

            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             * @param oAsyncResult
             */
            OnUploadProgressPrepared: function(oContext, oAsyncResult) {
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             * @param {ITHit.WebDAV.Client.Upload.ContentWriter~event:OnFinish} oEventData
             */
            OnContentCompleted: function(oContext, oEventData) {

            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadError~Result} oResult
             */
            OnRetryResult: function(oContext, oResult) {

            }

        });
})();


(function() {
    'use strict';

    /**
     * @class ITHit.WebDAV.Client.Upload.States.CompletedState
     * @extends ITHit.WebDAV.Client.Upload.States.BaseState
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.States.CompletedState',
        ITHit.WebDAV.Client.Upload.States.BaseState,
        /** @lends ITHit.WebDAV.Client.Upload.States.CompletedState.prototype */ {


            /**
             * @inheritDoc
             */
            GetAsEnum: function(){
                return ITHit.WebDAV.Client.Upload.State.Completed;
            },

            OnEnter: function(oContext){
                oContext.GetProgressTracker().StopTracking();
                oContext.GetProgressTracker().SetCompleted();
            },

            /**
             * @inheritDoc
             */
            StartUploadAsync: function(oContext,fCallback) {
                oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetUploadingState());
                this._super(oContext, fCallback);
            }


        });
})();


(function() {
    'use strict';

    /**
     * @class ITHit.WebDAV.Client.Upload.States.SkippedState
     * @extends ITHit.WebDAV.Client.Upload.States.BaseState
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.States.SkippedState',
        ITHit.WebDAV.Client.Upload.States.BaseState,
        /** @lends ITHit.WebDAV.Client.Upload.States.SkippedState.prototype */ {

            /**
             * @override
             */
            GetAsEnum: function(){
                return ITHit.WebDAV.Client.Upload.State.Skipped;
            },

            /**
             * @inheritDoc
             */
            StartUploadAsync: function(oContext, fCallback) {
                oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetUploadingState());
                this._super(oContext, fCallback);
            }

        });
})();


(function() {
    'use strict';

    /**
     * @class ITHit.WebDAV.Client.Upload.States.QueuedState
     * @extends ITHit.WebDAV.Client.Upload.States.BaseState
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.States.QueuedState',
        ITHit.WebDAV.Client.Upload.States.BaseState,
        /** @lends ITHit.WebDAV.Client.Upload.States.QueuedState.prototype */ {

            /**
             * @override
             */
            GetAsEnum: function() {
                return ITHit.WebDAV.Client.Upload.State.Queued;
            },


            StartUploadAsync: function(oContext, fCallback) {
                oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetUploadingState());
                this._super(oContext, fCallback);
            },

            Skip: function(oContext) {
                oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetSkippedState());
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             * @param {number} iTryCount
             * @param {number} iRepeatTime
             * @param {Function} fCallback
             */
            AbortUpload: function(oContext, iTryCount, iRepeatTime, fCallback) {
                oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetCanceledState());
                this._super(oContext, iTryCount, iRepeatTime, fCallback);
            }

        });
})();


(function() {
    'use strict';

    /**
     * @class ITHit.WebDAV.Client.Upload.States.CanceledState
     * @extends ITHit.WebDAV.Client.Upload.States.BaseState
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.States.CanceledState',
        ITHit.WebDAV.Client.Upload.States.BaseState,
        /** @lends ITHit.WebDAV.Client.Upload.States.CanceledState.prototype */ {

            /**
             * @override
             */
            GetAsEnum: function() {
                return ITHit.WebDAV.Client.Upload.State.Canceled;
            },

            OnEnter: function(oContext){
                oContext.GetProgressTracker().StopTracking();
                oContext.GetProgressTracker().Reset();
            },

            /**
             * @inheritDoc
             */
            StartUploadAsync: function(oContext, fCallback) {
                oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetUploadingState());
                this._super(oContext, fCallback);
            }

        });
})();


(function() {
    'use strict';

    /**
     * @class ITHit.WebDAV.Client.Upload.States.UploadingState
     * @extends ITHit.WebDAV.Client.Upload.States.BaseState
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.States.UploadingState',
        ITHit.WebDAV.Client.Upload.States.BaseState,
        /** @lends ITHit.WebDAV.Client.Upload.States.UploadingState.prototype */ {

            /**
             * @return {string}
             */
            GetAsEnum: function() {
                return ITHit.WebDAV.Client.Upload.State.Uploading;
            },


            /**
             * @inheritDoc
             * @param {ITHit.WebDAV.Client.Upload.Providers.UploadProvider} oContext
             */
            OnEnter: function(oContext){
                oContext.PrepareUploadLocation();
            },

            _PauseCompletedAsync: function(oContext, fCallback, thisArg) {
                if (oContext.IsRetrySchedule){
                    oContext.IsRetrySchedule = false;
                }
                oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetPausedState());
                fCallback.call(thisArg);
            },
            /**
             * @override
             */
            PauseUpload: function(oContext, fCallback) {
                oContext._ProgressTracker.StopTracking();
                oContext.CancelAllRequests(function(){
                    if (oContext.IsContentSend) {
                        oContext.SyncProgressWithServerAsync(function(oAsyncResult){
                            this._PauseCompletedAsync(oContext, fCallback);
                        }, this);
                        return;
                    }

                    this._PauseCompletedAsync(oContext, fCallback);
                }, this);
            },

            /**
             * @param {number} iTryCount
             * @param {number} iRepeatTime
             * @param {Function} fCallback
             */
            AbortUpload: function(oContext, iTryCount, iRepeatTime, fCallback) {
                oContext.CancelAllRequests(function(){
                    oContext.GetProgressTracker().StopTracking();
                    oContext.CancelAndDeleteAsync(iTryCount, iRepeatTime, function(oAsyncResult) {
                        if (oAsyncResult.IsSuccess) {
                            oContext.GetProgressTracker().Reset();
                            oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetCanceledState());
                        } else {
                            oContext.AddError(oAsyncResult.Error);
                            oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetFailedState());
                        }
                        fCallback();
                    }, this);
                }, this);
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.ContentWriter~event:OnFinish} oEventData
             * @private
             */
            OnContentCompleted: function(oContext, oEventData) {
                var oResult = oEventData.Result;
                if (oResult.IsAborted) {
                    return;
                }

                if (oResult.IsSuccess) {
                    oContext.GetProgressTracker().SetCompleted();
                    oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetCompletedState());
                    return;
                }

                this._HandleError(oContext, oResult);
            },

            _HandleError: function(oContext, oResult) {
                oContext.AddError(oResult.Error);
                oContext.BeginRetry(oResult.Error);
            },

            OnRetryResult: function(oContext, oResult) {
                if (oResult.Action === 'skip') {
                    oContext.AddError(oResult.Error);
                    oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetFailedState());
                    return;
                }

                if (oContext.IsContentSend) {
                    oContext.SyncProgressWithServerAsync(function(oAsyncResult){
                        if (oAsyncResult.Error) this._HandleError(oResult.Error);
                        else this.OnEnter(oContext);
                    }, this);
                    return;
                }

                this.OnEnter(oContext);
            },
            OnUploadLocationPrepared: function(oContext, oAsyncResult) {
                if (oAsyncResult.IsAborted) return;
                if (!oAsyncResult.IsSuccess) {
                    this._HandleError(oContext, oAsyncResult);
                    return;
                }
                oContext._SendContent();
            }
        });
})();


(function() {
    'use strict';

    /**
     * @class ITHit.WebDAV.Client.Upload.States.ResumeState
     * @extends ITHit.WebDAV.Client.Upload.States.UploadingState
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.States.ResumeState',
        ITHit.WebDAV.Client.Upload.States.UploadingState,
        /** @lends ITHit.WebDAV.Client.Upload.States.ResumeState.prototype */ {


            /**
             * @override
             */
            OnEnter: function(oContext){
                if (oContext.IsContentSend) {
                    oContext.PrepareProgress();
                    return;
                }

                this._super(oContext);
            },


            OnUploadProgressPrepared: function(oContext, oAsyncResult) {
                if (oAsyncResult.IsAborted) return;
                if (!oAsyncResult.IsSuccess) {
                    this._HandleError(oContext, oAsyncResult);
                    return;
                }

                if (oContext.GetProgressTracker().IsCompleted()) {
                    oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetCompletedState());
                }

                oContext._SendContent();
            }
        });
})();


(function() {
    'use strict';

    /**
     * @class ITHit.WebDAV.Client.Upload.States.PausedState
     * @extends ITHit.WebDAV.Client.Upload.States.BaseState
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.States.PausedState',
        ITHit.WebDAV.Client.Upload.States.BaseState,
        /** @lends ITHit.WebDAV.Client.Upload.States.PausedState.prototype */ {

            /**
             * @override
             */
            GetAsEnum: function() {
                return ITHit.WebDAV.Client.Upload.State.Paused;
            },

            OnEnter: function(oContext) {
                oContext.GetProgressTracker().StopTracking();
                oContext.GetProgressTracker().ResetSpeed();
            },

            /**
             * @public
             * @param {Function} fCallback
             */
            StartUploadAsync: function(oContext, fCallback) {
                oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetResumeState());
                this._super(oContext, fCallback);
            },

            /**
             * @param {number} iTryCount
             * @param {number} iRepeatTime
             * @param {Function} fCallback
             */
            AbortUpload: function(oContext, iTryCount, iRepeatTime, fCallback) {
                if (oContext.IsContentSend) {
                    oContext.CancelAndDeleteAsync(iTryCount, iRepeatTime, function(oAsyncResult) {
                        if (oAsyncResult.IsSuccess) {
                            oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetCanceledState());
                        }
                        else {
                            oContext.AddError(oAsyncResult.Error);
                            oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetFailedState());
                        }
                        fCallback();
                    }, this);
                }
                else {
                    oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetCanceledState());
                    fCallback();
                }
            }
        });
})();


(function() {
    'use strict';



    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.States.FailedState',
        ITHit.WebDAV.Client.Upload.States.BaseState,
        /** @lends ITHit.WebDAV.Client.Upload.States.FailedState.prototype */ {

            /**
             * @override
             */
            GetAsEnum: function(){
                return ITHit.WebDAV.Client.Upload.State.Failed;
            },

            OnEnter: function(oContext){
                oContext.GetProgressTracker().StopTracking();
                oContext.GetProgressTracker().ResetSpeed();
            },

            /**
             * @inheritDoc
             */
            StartUploadAsync: function(oContext, fCallback) {
                oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetUploadingState());
                this._super(oContext, fCallback);
            },

            /**
             * @param {number} iTryCount
             * @param {number} iRepeatTime
             * @param {Function} fCallback
             */
            AbortUpload: function(oContext, iTryCount, iRepeatTime, fCallback) {
                if (oContext.IsContentSend) {
                    oContext.CancelAndDeleteAsync(iTryCount, iRepeatTime, function(oAsyncResult) {
                        if (oAsyncResult.IsSuccess) {
                            oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetCanceledState());
                        }
                        else {
                            oContext.AddError(oAsyncResult.Error);
                            oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetFailedState());
                        }
                        fCallback();
                    }, this);
                } else {
                    oContext.SetState(ITHit.WebDAV.Client.Upload.States.Factory.GetCanceledState());
                    fCallback();
                }
            }
        });
})();


/**
 * This class provides settings for Uploader.
 * @api
 * @class ITHit.WebDAV.Client.Upload.Settings
 */
(function() {
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Settings',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Settings.prototype */
        {
            /**
             * Number of active uploads same time.
             * Number of concurrent uploads.
             * @api
             * @type {number}
             * @default 2
             */
            ConcurrentUploads: 2,

            /**
             * Default queue state.
             * @api
             * @type {(ITHit.WebDAV.Client.Upload.State.Queued | ITHit.WebDAV.Client.Upload.State.UploadItem|string)}
             * @default ITHit.WebDAV.Client.Upload.State.Queued
             */
            State: ITHit.WebDAV.Client.Upload.State.Queued,

            /**
             * Default cancel behaviour.
             * @api
             * @type {!boolean}
             * @default true
             */
            DeleteOnCancel: true
        });
})();

(function() {
    'use strict';

    /**
     * Creates upload states as singletons.
     * @class ITHit.WebDAV.Client.Upload.States.Factory
     */
    var self = ITHit.DefineClass('ITHit.WebDAV.Client.Upload.States.Factory',
        null,
        {},
        /** @lends ITHit.WebDAV.Client.Upload.States.Factory */ {

            /**
             * Returns Uploading state.
             * @return {ITHit.WebDAV.Client.Upload.States.BaseState} The states instance.
             */
            GetUploadingState: function() {
                if (!self._UploadingState) {
                    self._UploadingState = new ITHit.WebDAV.Client.Upload.States.UploadingState();
                }

                return self._UploadingState;
            },
            /**
             * Returns Skipped state.
             * @return {ITHit.WebDAV.Client.Upload.States.BaseState} The states instance.
             */
            GetSkippedState: function() {
                if (!self._SkippedState) {
                    self._SkippedState = new ITHit.WebDAV.Client.Upload.States.SkippedState();
                }

                return self._SkippedState;
            },

            /**
             * Returns Queued state.
             * @return {ITHit.WebDAV.Client.Upload.States.BaseState} The states instance.
             */
            GetQueuedState: function() {
                if (!self._QueuedState) {
                    self._QueuedState = new ITHit.WebDAV.Client.Upload.States.QueuedState();
                }

                return self._QueuedState;
            },
            /**
             * Returns Paused state.
             * @return {ITHit.WebDAV.Client.Upload.States.BaseState} The states instance.
             */
            GetPausedState: function() {
                if (!self._PausedState) {
                    self._PausedState = new ITHit.WebDAV.Client.Upload.States.PausedState();
                }

                return self._PausedState;
            },
            /**
             * Returns Failed state.
             * @return {ITHit.WebDAV.Client.Upload.States.BaseState} The states instance.
             */
            GetFailedState: function() {
                if (!self._FailedState) {
                    self._FailedState = new ITHit.WebDAV.Client.Upload.States.FailedState();
                }

                return self._FailedState;
            },
            /**
             * Returns Completed state.
             * @return {ITHit.WebDAV.Client.Upload.States.BaseState} The states instance.
             */
            GetCompletedState: function() {
                if (!self._CompletedState) {
                    self._CompletedState = new ITHit.WebDAV.Client.Upload.States.CompletedState();
                }

                return self._CompletedState;
            },
            /**
             * Returns Canceled state.
             * @return {ITHit.WebDAV.Client.Upload.States.BaseState} The states instance.
             */
            GetCanceledState: function() {
                if (!self._CanceledState) {
                    self._CanceledState = new ITHit.WebDAV.Client.Upload.States.CanceledState();
                }

                return self._CanceledState;
            },
            /**
             * Returns Resume state.
             * @return {ITHit.WebDAV.Client.Upload.States.BaseState} The states instance.
             */
            GetResumeState: function() {
                if (!self._ResumeState) {
                    self._ResumeState = new ITHit.WebDAV.Client.Upload.States.ResumeState();
                }

                return self._ResumeState;
            },

            /**
             * Returns state from enum.
             * @param {ITHit.WebDAV.Client.Upload.State} oState The state to create.
             * @return {ITHit.WebDAV.Client.Upload.States.BaseState} Created state.
             */
            GetState: function(oState) {
                switch (oState) {
                    case ITHit.WebDAV.Client.Upload.State.Canceled:
                        return self.GetCanceledState();
                    case ITHit.WebDAV.Client.Upload.State.Completed:
                        return self.GetCompletedState();
                    case ITHit.WebDAV.Client.Upload.State.Failed:
                        return self.GetFailedState();
                    case ITHit.WebDAV.Client.Upload.State.Paused:
                        return self.GetPausedState();
                    case ITHit.WebDAV.Client.Upload.State.Queued:
                        return self.GetQueuedState();
                    case ITHit.WebDAV.Client.Upload.State.Skipped:
                        return self.GetSkippedState();
                    case ITHit.WebDAV.Client.Upload.State.Uploading:
                        return self.GetUploadingState();
                    default:
                        throw new ITHit.Exceptions.ArgumentException(null, 'oState');
                }
            }
        });
})();


/**
 * @class ITHit.WebDAV.Client.Upload.ItemSettings
 */
(function() {
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.ItemSettings',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.ItemSettings.prototype */
        {
            /**
             * @type {boolean}
             */
            ForceRewrite: false,

            /**
             * @type {boolean}
             */
            AlwaysRewriteFolders: true,

            /**
             * @type {boolean}
             */
            IgnoreCancelErrors: false,

            /**
             * @type {boolean}
             */
            DeleteOnCancel: false
        });
})();

(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.ServerItem',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.ServerItem.prototype */ {
            /**
             * @alias ITHit.WebDAV.Client.Upload.ServerItem
             * @constructs
             * @param {ITHit.WebDAV.Client.Upload.UploaderSession} oSession
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             */
            constructor: function(oSession, oUrl) {
                this._Session = oSession;
                this._Url = oUrl;
            },

            GetProgressAsync: function(fCallback, thisArg) {
                return this._Session.GetProgressReportAsync(this._Url.GetHref(), function(oAsyncResult) {
                    if (oAsyncResult.IsSuccess && oAsyncResult.Result[0]) {
                        var oServerProgress = oAsyncResult.Result[0];
                        fCallback.call(thisArg, ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult(oServerProgress));
                        return;
                    }

                    fCallback.call(thisArg, oAsyncResult);
                }, this);
            },

            CancelUploadAsync: function(fCallback, thisArg) {
                this._Session.CancelUploadAsync(this._Url.GetHref(), function(oAsyncResult) {
                    fCallback.call(thisArg, oAsyncResult);
                });
            },

            /**
             * @param {Function} fCallback
             * @param {Object} thisArg
             */
            DeleteAsync: function(iTryCount, iRepeatTime, fCallback, thisArg) {
                var that = this;
                /** @type {ITHit.WebDAV.Client.Upload.Utils.RepeatableAction<ITHit.WebDAV.Client.AsyncResult>} */
                var oRepeatable = new ITHit.WebDAV.Client.Upload.Utils.RepeatableAction(function(oContext) {
                    that._Session.DeleteAsync( that._Url.GetHref(), null, function(oAsyncResult) {
                        if (oAsyncResult.IsSuccess) oContext.Stop(oAsyncResult);
                        else oContext.EndRound(oAsyncResult);
                    });
                });

                oRepeatable.RunAsync(iTryCount, iRepeatTime, function(oResult) {
                    fCallback.call(thisArg, oResult);
                });
            },

            CancelAndDeleteAsync: function(iTryCount, iRepeatTime, fCallback, thisArg) {
                this.CancelUploadAsync(function(oAsyncResult) {
                    if (!oAsyncResult.IsSuccess) return fCallback.call(thisArg, oAsyncResult);
                    this.DeleteAsync(iTryCount, iRepeatTime, fCallback, thisArg);
                }, this);
            },

            /**
             * @type {ITHit.WebDAV.Client.Upload.Utils.DavUrl}
             */
            _Url: null,

            /**
             * @type {ITHit.WebDAV.Client.Upload.UploaderSession}
             */
            _Session: null

        });
})();


(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Providers.UploadProvider',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Providers.UploadProvider.prototype */
        {

            /**
             * @type {ITHit.WebDAV.Client.Upload.UploaderSession}
             */
            Session: null,

            /**
             * @type {ITHit.WebDAV.Client.Upload.UploadItem}
             */
            _UploadItem: null,

            /**
             *
             * @public
             * @alias ITHit.WebDAV.Client.Upload.Providers.UploadProvider
             * @classdesc This class provides methods for performing and manage upload process.
             * @constructs
             * @param {ITHit.WebDAV.Client.Upload.UploaderSession} oSession
             * @param {ITHit.WebDAV.Client.Upload.UploadItem} UploadItem
             * @param {ITHit.WebDAV.Client.Upload.FSEntry} oFsEntry
             * @param {ITHit.WebDAV.Client.Upload.Utils.DavUrl} oUrl
             * @param {ITHit.WebDAV.Client.Upload.Settings} oSettings
             */
            constructor: function(oSession, UploadItem, oFsEntry, oUrl, oSettings) {
                this.FSEntry = oFsEntry;
                this.Url = oUrl;
                this.Settings = new ITHit.WebDAV.Client.Upload.ItemSettings();
                if (this.FSEntry.IsFile()) {
                    this.Settings.DeleteOnCancel = oSettings.DeleteOnCancel;
                } else {
                    this.Settings.DeleteOnCancel = false;
                }

                this.Session = oSession;
                this._UploadItem = UploadItem;
                this._ProgressTracker = new ITHit.WebDAV.Client.Upload.Providers.ProgressTracker(this.FSEntry.GetSize());
                this._State = ITHit.WebDAV.Client.Upload.States.Factory.GetState(oSettings.State);
                this.Errors = [];
                this.UploadLocation = oSession.CreateUploadLocation(this.Url);
                this.ServerItem = new ITHit.WebDAV.Client.Upload.ServerItem(oSession, this.Url);
                this.ContentWriter = oSession.CreateContentWriter(this.Url);
                this.ContentWriter.AddListener(ITHit.WebDAV.Client.Upload.ContentWriter.EVENT_ON_PROGRESS, this.OnRequestProgressEventHandler, this);
                this.ContentWriter.AddListener(ITHit.WebDAV.Client.Upload.ContentWriter.EVENT_ON_FINISH, this._LoadHandler, this);
                this.ContentWriter.AddListener(ITHit.WebDAV.Client.Upload.ContentWriter.EVENT_ON_START, this._StartLoadHandler, this);
                this._ProgressTracker.OnProgressChanged(this._SetProgress, this);
            },


            /**
             * @public
             */
            StartUploadAsync: function(fCallback) {
                this._BeginStateChange();
                this._State.StartUploadAsync(this, fCallback);
            },

            PauseUpload: function(fCallback) {
                this._BeginStateChange();
                this._State.PauseUpload(this, fCallback);
            },

            /**
             * @param {number} iTryCount
             * @param {number} iRepeatTime
             * @param {Function} fCallback
             */
            AbortUpload: function(iTryCount, iRepeatTime, fCallback) {
                this._BeginStateChange();
                fCallback = fCallback || function() {
                };
                this._State.AbortUpload(this, iTryCount, iRepeatTime, fCallback);
            },

            Skip: function() {
                this._BeginStateChange();
                this._State.Skip(this);
            },


            /**
             * @return {ITHit.WebDAV.Client.Upload.Groups.Group}
             */
            GetGroup: function() {
                return this._UploadItem.GetGroup();
            },

            /**
             *
             * @return {ITHit.WebDAV.Client.Upload.Providers.ProgressTracker}
             */
            GetProgressTracker: function() {
                return this._ProgressTracker;
            },

            /**
             * Current upload progress.
             * @private
             * @type {ITHit.WebDAV.Client.Upload.Providers.ProgressTracker}
             */
            _ProgressTracker: null,

            /**
             * Add event handlers.
             * @param {string} sEventName The event name to handle.
             * @param {Function} fCallback The callback to call.
             * @param {object} [oContext] The context to callback is called with.
             */
            AddListener: function(sEventName, fCallback, oContext) {
                this._ValidateEventName(sEventName);
                oContext = oContext || null;
                ITHit.Events.AddListener(this, sEventName, fCallback, oContext);
            },

            /**
             * Remove event listener.
             * @param {string} sEventName The event name to remove.
             * @param {Function} fCallback The callback to call.
             * @param {object} [oContext] The context to callback is called with.
             */
            RemoveListener: function(sEventName, fCallback, oContext) {
                this._ValidateEventName(sEventName);
                oContext = oContext || null;
                ITHit.Events.RemoveListener(this, sEventName, fCallback, oContext);
            },

            /**
             * @param {string} sEventName
             * @private
             */
            _ValidateEventName: function(sEventName) {
                switch (sEventName) {
                    case ITHit.WebDAV.Client.Upload.Events.EventName.OnStateChanged:
                    case ITHit.WebDAV.Client.Upload.Events.EventName.OnError:
                    case ITHit.WebDAV.Client.Upload.Events.EventName.OnProgressChanged:
                        break;

                    default:
                        throw new ITHit.Exceptions.ArgumentException('Not found event name `' + sEventName + '`');
                }
            },

            CheckRetryAsync: function(oError, fCallback, thisArg) {
                var oUploadError = new ITHit.WebDAV.Client.Upload.Events.UploadError(this._UploadItem, oError, function(oResult) {
                    if (!this.IsRetrySchedule) return;
                    fCallback.call(thisArg, oResult);
                }.bind(this));

                if (!this._UploadItem.OnUploadErrorCallback && (ITHit.Events.ListenersLength(this._UploadItem, oUploadError.Name) === 0)) {
                    fCallback.call(thisArg, ITHit.WebDAV.Client.Upload.Events.UploadError.GetSkipResult(oError));
                    return;
                }

                this.IsRetrySchedule = true;
                if (this._UploadItem.OnUploadErrorCallback) {
                    this._UploadItem.OnUploadErrorCallback.call(this, oUploadError);
                }

                ITHit.Events.DispatchEvent(this._UploadItem, oUploadError.Name, oUploadError);
            },

            /**
             * Stores all error that was added to this provider.
             * @public
             * @type {Error[]|ITHit.WebDAV.Client.Exceptions.WebDavException[]}
             */
            Errors: null,

            /**
             * Stores last error that was added to this provider.
             * @public
             * @type {Error|ITHit.WebDAV.Client.Exceptions.WebDavException}
             */
            LastError: null,

            /**
             * Adds error to provider and fires corresponding event.
             * @public
             * @param {Error|ITHit.WebDAV.Client.Exceptions.WebDavException} oError - The to be passed to events and added to list.
             */
            AddError: function(oError) {
                this.AddErrorSilent(oError)
                this._RiseOnErrorEvent(oError);
            },

            /**
             * Adds error to provider and doesn't fire corresponding event.
             * @param {Error|ITHit.WebDAV.Client.Exceptions.WebDavException} oError - The to be passed to events and added to list.
             * @public
             */
            AddErrorSilent: function(oError) {
                this.LastError = oError;
                this.Errors.push(oError);
            },

            /**
             * Sets failed state.
             * Populates item's error with provided error instance.
             * @param {ITHit.WebDAV.Client.Exceptions.WebDavException} oError - The error instance that will be registered as fail reason.
             */
            SetFailed: function(oError) {
                var oFailedState = ITHit.WebDAV.Client.Upload.States.Factory.GetFailedState();
                this.AddError(oError);
                this.SetState(oFailedState);
            },

            /**
             *
             * @param {Error|ITHit.WebDAV.Client.Exceptions.WebDavException} oError
             * @private
             */
            _RiseOnErrorEvent: function(oError) {
                var oEvent = new ITHit.WebDAV.Client.Upload.Events.Error(this, oError);
                ITHit.Events.DispatchEvent(this, oEvent.Name, oEvent);
            },


            /**
             * @type {ITHit.WebDAV.Client.Upload.UploadLocation}
             */
            UploadLocation: null,
            IsContentSend: false,

            /**
             * @type {ITHit.WebDAV.Client.Upload.ServerItem}
             */
            ServerItem: null,


            /**
             * @param {ITHit.WebDAV.Client.Upload.ContentWriter~event:OnFinish} oEventData
             * @private
             */
            _LoadHandler: function(oEventData) {
                if (oEventData.Result.Error instanceof ITHit.WebDAV.Client.Exceptions.ConflictException) {
                    this.UploadLocation.SetNotExists();
                    this.IsContentSend = false;
                }
                this._State.OnContentCompleted(this, oEventData);
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.ContentWriter~event:OnStart} oEventData
             * @private
             */
            _StartLoadHandler: function(oEventData) {
                this.IsContentSend = true;
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.ContentWriter~event:OnProgress} oEventData
             */
            OnRequestProgressEventHandler: function(oEventData) {
                this.GetProgressTracker().UpdateBytes(oEventData.Progress.BytesLoaded, oEventData.Progress.TotalBytes);
            },

            _SendContent: function() {
                this._ProgressTracker.StartTracking();
                if (this.Settings && this.Settings.CustomHeaders) {
                    this.ContentWriter.CustomHeaders = this.Settings.CustomHeaders;
                }
                if (this.FSEntry.IsFolder()) {
                    if (this.Settings.ForceRewrite || this.Settings.AlwaysRewriteFolders) {
                        this.ContentWriter.BeginRewrite(this.FSEntry);
                    } else {
                        this.ContentWriter.BeginWrite(this.FSEntry);
                    }
                }

                else {
                    var oSpan = new ITHit.WebDAV.Client.Upload.FileSpan(this.FSEntry.GetFile(), this._ProgressTracker.GetProgress().UploadedBytes);
                    if (oSpan.IsFullFile() && (this.Settings.ForceRewrite || this.IsContentSend)) {
                        this.ContentWriter.BeginRewrite(this.FSEntry);
                        return;
                    }
                    if (oSpan.IsFullFile() && !(this.Settings.ForceRewrite && this.IsContentSend)) {
                        this.ContentWriter.BeginWrite(this.FSEntry);
                        return;
                    }

                    this.ContentWriter.BeginAppend(oSpan);
                }
            },


            SyncProgressWithServerAsync: function(fCallback, thisArg) {
                if (!this._ProgressTracker.IsCountable()) {
                    return this.Session.CheckExistsAsync(this.Url.GetUrl(), function(oAsyncResult) {
                        if (!oAsyncResult.IsSuccess) {
                            fCallback.call(thisArg, oAsyncResult);
                            return;
                        }

                        if (oAsyncResult.Result === true) {
                            this._ProgressTracker.SetCompleted();
                            fCallback.call(thisArg, ITHit.WebDAV.Client.CancellableResult.CreateSuccessfulResult(this._ProgressTracker.GetProgress()));
                            return;
                        }

                        this._ProgressTracker.Reset();
                        fCallback.call(thisArg, ITHit.WebDAV.Client.CancellableResult.CreateSuccessfulResult(this._ProgressTracker.GetProgress()));
                    }, this);
                }

                return this.ServerItem.GetProgressAsync(function(oAsyncResult) {
                    if (oAsyncResult.IsSuccess) {
                        this._ProgressTracker.SyncProgress(oAsyncResult.Result);
                        fCallback.call(thisArg, ITHit.WebDAV.Client.CancellableResult.CreateSuccessfulResult(this._ProgressTracker.GetProgress()));
                        return;
                    }

                    if (oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.NotFoundException) {
                        this._ProgressTracker.Reset();
                        fCallback.call(thisArg, ITHit.WebDAV.Client.CancellableResult.CreateSuccessfulResult(this._ProgressTracker.GetProgress()));
                        return;
                    }
                    fCallback.call(thisArg, ITHit.WebDAV.Client.CancellableResult.CreateFailedResult(oAsyncResult.Error));
                }, this);
            },

            IsRetrySchedule: false,

            PrepareUploadLocation: function() {
                this.UploadLocation.SetCache(this.GetGroup().PathMap);
                this.UploadLocation.CreateAsync(this._OnGeneratePathCompleted, this);
            },

            _OnGeneratePathCompleted: function(oAsyncResult) {
                if (oAsyncResult.IsAborted) return;
                this._State.OnUploadLocationPrepared(this, oAsyncResult);
            },

            CancelAllRequests: function(fCallback, thisArg) {
                this._CancelProgressAsync(function() {
                    this._CancelLocationCreateAsync(function() {
                        this._CancelContentSendingAsync(fCallback, thisArg);
                    }, this);
                }, this);
            },

            _CancelLocationCreateAsync: function(fCallback, thisArg) {
                if (this.UploadLocation.IsInProgress()) {
                    this.UploadLocation.AbortRunningCreationAsync(function() {
                        fCallback.call(thisArg);
                    }, this);
                }
                else {
                    fCallback.call(thisArg);
                }
            },

            _CancelContentSendingAsync: function(fCallback, thisArg) {
                if (this.ContentWriter.IsActive()) {
                    this.ContentWriter.AbortAsync(function() {
                        fCallback.call(thisArg);
                    }, this);
                }
                else {
                    fCallback.call(thisArg);
                }
            },

            _CancelProgressAsync: function(fCallback, thisArg) {
                if (this.IsProgressSyncInProgress) {
                    this._SyncProgressRequest.AbortAsync(function() {
                        fCallback.call(thisArg);
                    }, this);
                }
                else {
                    fCallback.call(thisArg);
                }
            },

            _SyncProgressRequest: null,
            IsProgressSyncInProgress: false,
            PrepareProgress: function() {
                this._SyncProgressRequest = this.SyncProgressWithServerAsync(this._OnUpdateFromServerCompleted, this);
            },

            _OnUpdateFromServerCompleted: function(oAsyncResult) {
                this.IsProgressSyncInProgress = false;
                if (oAsyncResult.IsAborted) return;

                this._State.OnUploadProgressPrepared(this, oAsyncResult);
            },
            /**
             * @protected
             * @return {boolean}
             */
            _IsStateChanging: function() {
                return this._IsChanging;
            },


            /**
             * Set state.
             * @param {TState} oState
             */
            SetState: function(oState) {
                var oldState = this._State;
                this._State.OnLeave(this);
                this._State = oState;
                this._State.OnEnter(this);
                var oEvent = new ITHit.WebDAV.Client.Upload.Events.StateChanged(this, oldState.GetAsEnum(), this._State.GetAsEnum());
                ITHit.Events.DispatchEvent(this, oEvent.Name, oEvent);
            },

            /**
             * Gets current upload state.
             * @return {TState}
             */
            GetState: function() {
                return this._State;
            },


            /**
             * Current upload state.
             * @protected
             * @type {TState}
             */
            _State: null,

            /**
             * @private
             * @type {boolean}
             */
            _IsChanging: false,

            /**
             *
             * @protected
             */
            _BeginStateChange: function() {
                this._IsChanging = true;
            },

            /**
             *
             * @protected
             */
            _EndStateChange: function() {
                this._IsChanging = false;
            },

            /**
             * @type {ITHit.WebDAV.Client.Upload.ContentWriter}
             */
            ContentWriter: null,

            BeginRetry: function(oError) {
                this._ProgressTracker.StopTracking();
                this.CheckRetryAsync(oError, this._OnCheckRetryCompleted, this);
            },
            /**
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadError~Result} oResult
             */
            _OnCheckRetryCompleted: function(oResult) {
                this._State.OnRetryResult(this, oResult);
            },
            /**
             * @type {ITHit.WebDAV.Client.Upload.ItemSettings}
             */
            Settings: null,

            /**
             * @type {ITHit.WebDAV.Client.Upload.FSEntry}
             */
            FSEntry: null,
            /**
             * @type {ITHit.WebDAV.Client.Upload.Utils.DavUrl}
             */
            Url: null,
            CancelAndDeleteAsync: function(iTryCount, iRepeatTime, fCallback, thisArg) {
                this.ServerItem.CancelUploadAsync(function(oAsyncResult) {
                    if (!this.Settings.DeleteOnCancel) {
                        fCallback.call(thisArg, ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult(null));
                        return;
                    }
                    this.ServerItem.DeleteAsync(iTryCount, iRepeatTime, function(oDeleteResult) {
                        if (!oDeleteResult.IsSuccess && !this.Settings.IgnoreCancelErrors) return fCallback.call(thisArg, oAsyncResult);
                        this.IsContentSend = false;
                        fCallback.call(thisArg, ITHit.WebDAV.Client.AsyncResult.CreateSuccessfulResult(null));
                    }, this);
                }, this);
            },
            /**
             * Return current progress.
             * @public
             * @return {ITHit.WebDAV.Client.Upload.Progress} Current progress.
             */
            GetProgress: function() {
                return this._ProgressTracker.GetProgress();
            },

            /**
             * Set progress
             * @param {ITHit.WebDAV.Client.Upload.Progress} oProgress The progress object to set.
             * @private
             */
            _SetProgress: function(oProgress) {
                var oldProgress = this._Progress;
                this._Progress = oProgress;
                var oEvent = new ITHit.WebDAV.Client.Upload.Events.ProgressChanged(this, oldProgress, oProgress);
                ITHit.Events.DispatchEvent(this, oEvent.Name, oEvent);
            }
        });
})();


(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated',
        ITHit.WebDAV.Client.Upload.Events.AsyncEvent,
        /** @lends ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated.prototype */
        {

            /**
             * Added items.
             * @api
             * @type {ITHit.WebDAV.Client.Upload.UploadItem[]}
             */
            Items: [],


            /**
             * Skips collection of items. Ends callback handling.
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aSkippedItems
             */
            Skip: function(aSkippedItems) {
                if (this._IsHandled) return;
                this._Skip(aSkippedItems);
            },

            /**
             * Skips all items. Ends callback handling.
             */
            SkipAll: function() {
                if (this._IsHandled) return;
                this._Skip(this.Items);
            },

            /**
             * Overwrites all items. Ends callback handling.
             */
            OverwriteAll: function() {
                if (this._IsHandled) return;
                this._Overwrite(this.Items);
            },

            /**
             * Overwrites collection of items. Ends callback handling.
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aOverwrittenItems
             */
            Overwrite: function(aOverwrittenItems) {
                if (this._IsHandled) return;
                this._Overwrite(aOverwrittenItems);
            },

            /**
             * Uploads all items. Ends callback handling.
             */
            UploadAll: function() {
                if (this._IsHandled) return;
                this.Upload(this.Items);
            },

            /**
             * Continues items upload. Pass a list of items to upload.
             * If any items should not upload do not include them in this list.
             * If any items in the upload list should be overwritten call {@link ITHit.WebDAV.Client.Upload.UploadItem#SetOverwrite(true)}) on each item.
             * @api
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aItems - The list of items to be uploaded.  Items not listed here will be skipped.
             */
            Upload: function(aItems) {
                if (this._IsHandled) return;
                this._Handle({
                    Skip: [],
                    Overwrite: [],
                    Original: this.Items,
                    Upload: aItems
                });
            },

            /**
             * This object is passed to {@link ITHit.WebDAV.Client.Upload.Queue#event:OnUploadItemsCreated}  and contains list of items selected by user for upload.
             * You can validate these items as well as specify if item should be overwritten.
             * To continue upload the UploadItemsCreated.Upload() function with the list of items to be uploaded should be called.
             * @api
             * @alias ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated
             * @extends ITHit.WebDAV.Client.Upload.Events.AsyncEvent
             * @constructs
             * @param {ITHit.WebDAV.Client.Upload.UploadItem} oSender
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aItems
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated~ResultCallback} fCallback
             */
            constructor: function(oSender, aItems, fCallback) {
                this.Name = ITHit.WebDAV.Client.Upload.Events.EventName.OnUploadItemsCreated;
                this.Items = aItems || [];
                this._super(oSender, fCallback);
            },

            /**
             *
             * @private
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aItem
             */
            _Overwrite: function(aItems) {
                var oResult = this._CreateResult([], aItems);
                this._Handle(oResult);
            },

            /**
             *
             * @private
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aItems
             */
            _Skip: function(aItems) {
                var oResult = this._CreateResult(aItems, []);
                this._Handle(oResult);
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} [aSkip]
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} [aOverwrite]
             * @return {ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated~Result}
             * @private
             */
            _CreateResult: function(aSkip, aOverwrite){
                return {
                    Skip: aSkip || [],
                    Overwrite: aOverwrite || [],
                    Original: this.Items
                };
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated~Result} [oResult]
             * @private
             */
            _Handle: function(oResult) {
                oResult = oResult || this._CreateResult();
                this._super(oResult);
            }
        });
})();

/**
* @private
* @typedef {Object} ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated~Result
* @property {ITHit.WebDAV.Client.Upload.UploadItem[]} Skip
* @property {ITHit.WebDAV.Client.Upload.UploadItem[]} Original
* @property {ITHit.WebDAV.Client.Upload.UploadItem[]} Overwrite
* @property {ITHit.WebDAV.Client.Upload.UploadItem[]} Upload
*/

/**
 * @private
 * @callback ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated~ResultCallback
 * @param {ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated~Result} oResult
 */
(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Utils.Array',
        null,
        {},
        /** @lends ITHit.WebDAV.Client.Upload.Utils.Array */ {
            MapParallel: function(oArray, fMapCallback, fDoneCallback, thisArg) {
                var aResult = [];
                var iCounter = 0;
                if (oArray.length === 0) setTimeout(fDoneCallback.apply(thisArg, oArray));

                for (var i = 0; i < oArray.length; i++) {
                    fMapCallback.apply(thisArg,
                        [oArray[i], i, oArray, ITHit.Utils.MakeScopeClosure(this, function(i, oItem) {
                            aResult[i] = oItem;
                            iCounter++;
                            if (iCounter === oArray.length) {
                                setTimeout(fDoneCallback.call(thisArg, aResult));
                            }
                        }, i)]);
                }
            },

            /**
             * @template T
             * @param {T[]} oArray
             * @param {function} [fSelectCallback]
             * @param {Object} [thisArg]
             * @return {T[]}
             */
            DistinctBy: function(oArray, fSelectCallback, thisArg) {
                /** @type {Object.<string, T>} */
                var map = Object.create(null);
                fSelectCallback = fSelectCallback || Object.prototype.toString;
                for (var i = 0; i < oArray.length; i++) {
                    var sValue = fSelectCallback.call(thisArg, oArray[i]).toString();
                    if (!map[sValue]) map[sValue] = oArray[i];
                }

                return Object.keys(map).map(function(sKey) { return map[sKey]; });
            },

            /**
             * @template T
             * @param {T[]} oArray
             * @param {number} [iCount]
             * @return T[]
             */
            Take: function(oArray, iCount) {
                if (!iCount) {
                    return [oArray.shift()];
                }

                var Count = (oArray.length > iCount) ? iCount : oArray.length;
                var accumulator = [];
                for (var i = 0; i<Count; i++){
                    accumulator.push(oArray.shift());
                }

                return accumulator;
            },

            /**
             * @template T
             * @param {T[]} oArray
             * @param {T} [oItem]
             */
            Remove: function(oArray, oItem) {
                var index = oArray.indexOf(oItem);
                if (index > -1) {
                    oArray.splice(index, 1);
                }
            }
        });
})();


(function() {
    'use strict';

    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.AutoUploader',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.AutoUploader.prototype */ {

            /**
             * @alias ITHit.WebDAV.Client.Upload.AutoUploader
             * @constructs
             * @param {number} [iParallelUploads=0]
             */
            constructor: function(iParallelUploads){
                this._ParallelUploads = iParallelUploads || 0;
                this._QueueArray = [];
                this._Active = [];
                this._Reserve = 0;
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aItems
             */
            AddRange: function(aItems) {
                aItems.forEach(this._AddToQueue, this);
                this._StartUploads();
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.UploadItem} oUploadItem
             */
            Add: function(oUploadItem){
                this._AddToQueue(oUploadItem);
                this._StartUploads();
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.UploadItem} oUploadItem
             */
            Remove: function(oUploadItem){
                oUploadItem.RemoveListener(ITHit.WebDAV.Client.Upload.Events.EventName.OnStateChanged, this._OnStateChangeEventHandler, this);
                ITHit.WebDAV.Client.Upload.Utils.Array.Remove(this._QueueArray, oUploadItem);
                ITHit.WebDAV.Client.Upload.Utils.Array.Remove(this._Active, oUploadItem);
                this._StartUploads();
            },

            /**
             *
             * @param {number} [iCount=1]
             */
            Reserve: function(iCount){
                iCount = iCount || 1;
                this._Reserve += iCount;
            },

            /**
             * @param {number} [iCount=1]
             */
            Release: function(iCount){
                iCount = iCount || 1;
                this._Reserve -= iCount;
                this._StartUploads();
            },

            /**
             * @return {number}
             */
            GetBusy: function(){
                return this._Active.length + this._Reserve;
            },

            /**
             * @return {number}
             */
            GetFree: function() {
                var iBusy = this.GetBusy();
                if (iBusy >= this._ParallelUploads) {
                    return 0;
                } else if (iBusy === 0) {
                    return this._ParallelUploads;
                } else {
                    return (this._ParallelUploads - iBusy) % this._ParallelUploads;
                }
            },

            /**
             * @type {ITHit.WebDAV.Client.Upload.UploadItem[]}
             */
            _QueueArray: null,

            /**
             * @type {ITHit.WebDAV.Client.Upload.UploadItem[]}
             */
            _Active: null,

            /**
             * @type {number}
             */
            _ParallelUploads: 0,

            /**
             * 
             * @param {ITHit.WebDAV.Client.Upload.UploadItem~event:OnStateChanged} oOnStateChanged
             * @private
             */
            _OnStateChangeEventHandler: function(oOnStateChanged) {
                if (oOnStateChanged.NewState !== ITHit.WebDAV.Client.Upload.State.Uploading) {
                    this.Remove(oOnStateChanged.Sender);
                } else {
                    this._StartUploads();
                }
            },

            _StartUploads: function() {
                if (this._QueueArray.length === 0) return;

                var iUploadsCanStart = this.GetFree();
                if (iUploadsCanStart <= 0) return;

                var aCandidates = ITHit.WebDAV.Client.Upload.Utils.Array.Take(this._QueueArray, iUploadsCanStart);
                if (aCandidates.length < 1) return;
                this.Reserve(aCandidates.length);
                aCandidates.forEach(this._StartSingle, this);
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.UploadItem} oUploadItem
             */
            _StartSingle: function(oUploadItem){
                this._Active.push(oUploadItem);
                oUploadItem.StartAsync();
                this.Release();
            },

            /**
             *
             * @param {ITHit.WebDAV.Client.Upload.UploadItem} oUploadItem
             * @private
             */
            _AddToQueue: function(oUploadItem) {
                this._QueueArray.push(oUploadItem);
                oUploadItem.AddListener(ITHit.WebDAV.Client.Upload.Events.EventName.OnStateChanged, this._OnStateChangeEventHandler, this);
            },

            /**
             * @type {number}
             */
            _Reserve: 0
        });
})();


/**
 * Event reporting that queue changed. Fired when item is added or deleted from queue.
 * @api
 * @event ITHit.WebDAV.Client.Upload.Queue#OnQueueChanged
 * @property {ITHit.WebDAV.Client.Upload.Queue} Sender The queue instance.
 * @property {string} Name Event name.
 * @property {ITHit.WebDAV.Client.Upload.UploadItem[]} AddedItems Added items.
 * @property {ITHit.WebDAV.Client.Upload.UploadItem[]} RemovedItems Removed items.
 * @example
 *              var oUploader = new ITHit.WebDAV.Client.Upload.Uploader();
 *              oUploader.Queue.AddListener('OnQueueChanged', function (oQueueChanged) {
 *
 *                  oQueueChanged.AddedItems.forEach(function(element) {
 *                      console.log('Upload added:' + element.GetName());
 *                  });
 *               };
 */

/**
 * Event fired {@link ITHit.WebDAV.Client.Upload.UploadItem}s are created.
 * You will validate files selected for upload in this event and present user interface if user interaction is necessary.
 * In this event you can check if each item exists on the server and specify if item should be overwritten or skipped.
 * You can also validate file size, file extension, file upload path and file name.
 *
 * To continue upload the {@link ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated#Upload} function with the list of items to be uploaded should be called.
 * @api
 * @event ITHit.WebDAV.Client.Upload.Queue#OnUploadItemsCreated
 * @type {ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated}
 * @example
 * var oUploader = new ITHit.WebDAV.Client.Upload.Uploader();
 * oUploader.Queue.AddListener('OnUploadItemsCreated', function(oUploadItemsCreated) {
 *     var aIgnoredNames = ['file1.txt', 'file2.txt'];
 *
 *     /&#42;&#42; &#64;typedef {ITHit.WebDAV.Client.Upload.UploadItem[]} aItems &#42;/
 *     var aItems = oUploadItemsCreated.Items;
 *      /&#42;&#42; &#64;typedef {ITHit.WebDAV.Client.Upload.UploadItem[]} aItemsToUpload &#42;/
 *     var aItemsToUpload = aItems.filter(function(oItem) {
 *         aIgnoredNames.indexOf(oItem.GetName()) < 0
 *     }
 *
 *      oUploadItemsCreated.Upload(aItemsToUpload);
 * });
 *
 */

(function() {
    'use strict';

    /**
     * List of items being uploaded. Each item in the list describes the file
     * or folder upload state and provides methods for managing upload.
     * @api
     * @class ITHit.WebDAV.Client.Upload.Queue
     * @fires ITHit.WebDAV.Client.Upload.Queue#OnQueueChanged
     */
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Queue',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Queue.prototype */ {

            /**
             * Associated uploader.
             * @api
             * @type {ITHit.WebDAV.Client.Upload.Uploader}
             */
            Uploader: null,

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.UploadItem[]}
             */
            _UnderlyingArray: null,

            /**
             * @type {ITHit.WebDAV.Client.Upload.UploaderSession}
             */
            _Session: null,

            /**
             * @private
             * @type {ITHit.WebDAV.Client.Upload.AutoUploader}
             */
            _AutoUploader: null,

            constructor: function(oUploader) {
                this.Uploader = oUploader;
                this._Session = new ITHit.WebDAV.Client.Upload.UploaderSession();
                this._UnderlyingArray = [];
                this._GroupManager = new ITHit.WebDAV.Client.Upload.Groups.GroupManager();
                this._AutoUploader = new ITHit.WebDAV.Client.Upload.AutoUploader(this.Uploader.Settings.ConcurrentUploads);
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.UploadItem} oUploadItem
             * @return {boolean}
             */
            ShouldReplaceDuplicate: function(oUploadItem) {
                var oExistsUpload = this.GetByUrl(oUploadItem.GetUrl());
                var sState = oExistsUpload.GetState();
                return !(sState ===
                    ITHit.WebDAV.Client.Upload.State.Uploading ||
                    sState === ITHit.WebDAV.Client.Upload.State.Paused);
            },

            /**
             * Adds uploads to the queue.
             * @public
             * @param {string} sUrl Url to upload.
             * @param {ITHit.WebDAV.Client.Upload.FSEntry[]} aFSEntries Items to Upload.
             * @param {ITHit.WebDAV.Client.Upload.Controls.HtmlControl} [oSource] Source of items.
             */
            AddGroup: function(sUrl, aFSEntries, oSource) {
                var aPrepareFilesToUpload = [];
                for (var i = 0; i < aFSEntries.length; i++) {
                    var oFSEntry = aFSEntries[i];
                    var oUploadItem = new ITHit.WebDAV.Client.Upload.UploadItem(sUrl, oFSEntry, oSource, this._Session, this._GroupManager, this.Uploader.Settings);
                    if (this.HasUrl(oUploadItem.GetUrl())) {
                        if (this.ShouldReplaceDuplicate(oUploadItem)) {
                            this.RemoveByUrl(oUploadItem.GetUrl());
                        } else {
                            continue;
                        }
                    }
                    aPrepareFilesToUpload.push(oUploadItem);
                }

                this._DispatchOnUploadItemsCreatedAsync(aPrepareFilesToUpload, this._OnUploadItemsCreatedAsyncDispatched.bind(this));
            },

            /**
             * Adds {@link ITHit.WebDAV.Client.Upload.UploadItem} to the queue.
             * @private
             * @param {ITHit.WebDAV.Client.Upload.UploadItem} oUploadItem Item to add.
             */
            Add: function(oUploadItem) {
                var sUrl = oUploadItem.GetUrl();
                if (this.HasUrl(sUrl)) {
                    return;
                }

                this._UnderlyingArray.push(oUploadItem);
                var oNewEvent = new ITHit.WebDAV.Client.Upload.Events.QueueChanged(this, [oUploadItem]);
                ITHit.Events.DispatchEvent(this, oNewEvent.Name, [oNewEvent]);
                this._AutoUploader.Add(oUploadItem);
            },

            /**
             * Adds {@link ITHit.WebDAV.Client.Upload.UploadItem}s collection to the queue.
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aUploadItems Collection to add.
             */
            AddRange: function(aUploadItems) {
                for (var i = 0; i < aUploadItems.length; i++) {
                    var oUploadFile = aUploadItems[i];
                    var sUrl = oUploadFile.GetUrl();
                    if (this.HasUrl(sUrl)) {
                        continue;
                    }

                    this._UnderlyingArray.push(oUploadFile);
                }

                this._GroupManager.CreateGroup(aUploadItems);
                this._OnQueueChanged(aUploadItems, null);
                var aQueuedItems = aUploadItems.filter(function(oUploadItem) {
                    return oUploadItem.GetState() === ITHit.WebDAV.Client.Upload.State.Queued;
                });

                this._AutoUploader.AddRange(aQueuedItems);
            },

            /**
             * @api
             * Restart queued upload of {@link ITHit.WebDAV.Client.Upload.UploadItem}s collection.
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aUploadItems Collection restart.
             */
            Restart: function(aUploadItems) {
                for (var i = 0; i < aUploadItems.length; i++) {
                    if (!this.HasUrl(aUploadItems[i].GetUrl())) {
                        throw new ITHit.Exceptions.ArgumentException('Item should be a part of queue`');
                    }
                }

                this._AutoUploader.AddRange(aUploadItems);
            },

            /**
             * Get {@link ITHit.WebDAV.Client.Upload.UploadItem} by upload url.
             * @param {string} sUrl The url to identify upload.
             * @return {ITHit.WebDAV.Client.Upload.UploadItem|undefined}
             */
            GetByUrl: function(sUrl) {
                return ITHit.Utils.FindBy(this._UnderlyingArray,
                    function(oElement) {
                        return oElement.GetUrl() === sUrl;
                    });
            },

            /**
             * Get length of queue.
             * @return {number}
             */
            GetLength: function() {
                return this._UnderlyingArray.length;
            },

            /**
             * Check if queue contains upload with url.
             * @param {string} sUrl The url to test.
             * @return {boolean}
             */
            HasUrl: function(sUrl) {
                return !!this.GetByUrl(sUrl);
            },

            /**
             * Removes upload file from queue.
             * @param {string} sUrl The url of UploadItem to remove.
             * @api
             */
            RemoveByUrl: function(sUrl) {
                var oUploadItem = this.GetByUrl(sUrl);
                if (!oUploadItem) {
                    return;
                }

                var currentState = oUploadItem.GetState();
                if(currentState === ITHit.WebDAV.Client.Upload.State.Uploading ||
                    currentState === ITHit.WebDAV.Client.Upload.State.Paused) {
                    oUploadItem.Abort();
                }
                var index = ITHit.Utils.IndexOf(this._UnderlyingArray, oUploadItem);
                this._UnderlyingArray.splice(index, 1);
                this._OnQueueChanged(null, [oUploadItem]);
                this._AutoUploader.Remove(oUploadItem);
            },

            /**
             * Callback function called when {@link ITHit.WebDAV.Client.Upload.UploadItem}s are created.
             * You will validate files selected for upload in this event and present user interface if user interaction is necessary.
             * In this event you can check if each item exists on the server and specify if item should be overwritten or skipped.
             * You can also validate file size, file extension, file upload path and file name.
             *
             * To continue upload the {@link ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated#Upload} function with the list of items to be uploaded should be called.
             * @private
             * @callback ITHit.WebDAV.Client.Upload.Queue~OnUploadItemsCreatedCallback
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated} oEvent - Event Object
             * @example
             * var oUploader = new ITHit.WebDAV.Client.Upload.Uploader();
             * oUploader.Queue.OnUploadItemsCreatedCallback = function(oUploadItemsCreated) {
             *     var aIgnoredNames = ['file1.txt', 'file2.txt'];
             *
             *     /&#42;&#42; &#64;typedef {ITHit.WebDAV.Client.Upload.UploadItem[]} aItems &#42;/
             *     var aItems = oUploadItemsCreated.Items;
             *      /&#42;&#42; &#64;typedef {ITHit.WebDAV.Client.Upload.UploadItem[]} aItemsToUpload &#42;/
             *     var aItemsToUpload = aItems.filter(function(oItem) {
             *         aIgnoredNames.indexOf(oItem.GetName()) < 0
             *     }
             *
             *      oUploadItemsCreated.Upload(aItemsToUpload);
             * });
             *
             */

            /**
             * @private
             * @type {(ITHit.WebDAV.Client.Upload.Queue~OnUploadItemsCreatedCallback | null)}
             */
            OnUploadItemsCreatedCallback: null,

            /**
             *
             * @private
             * @param {(ITHit.WebDAV.Client.Upload.UploadItem[] | null)} aAdded
             * @param {(ITHit.WebDAV.Client.Upload.UploadItem[] | null)} aRemoved
             */
            _OnQueueChanged: function(aAdded, aRemoved) {
                var oNewEvent = new ITHit.WebDAV.Client.Upload.Events.QueueChanged(this, aAdded, aRemoved);
                ITHit.Events.DispatchEvent(this, oNewEvent.Name, [oNewEvent]);
            },

            /**
             * Dispatches event before add items
             * @private
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aItems
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated~ResultCallback} fCallback
             */
            _DispatchOnUploadItemsCreatedAsync: function(aItems, fCallback) {
                var oEvent = new ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated(this, aItems.slice(), fCallback);
                if (!this.OnUploadItemsCreatedCallback && (ITHit.Events.ListenersLength(this, oEvent.Name) === 0))
                {
                    oEvent.OverwriteAll();
                }

                if (this.OnUploadItemsCreatedCallback) {
                    this.OnUploadItemsCreatedCallback(oEvent);
                }

                ITHit.Events.DispatchEvent(this, oEvent.Name, oEvent);
            },

            /**
             * Add event handlers.
             * @api
             * @param {string} sEventName The event name to handle.
             * @param {Function} fCallback The callback to call.
             * @param {Object} [oContext] The context to callback is called with.
             */
            AddListener: function(sEventName, fCallback, oContext) {
                oContext = oContext || null;

                switch (sEventName) {
                    case ITHit.WebDAV.Client.Upload.Events.EventName.OnQueueChanged:
                    case ITHit.WebDAV.Client.Upload.Events.EventName.OnUploadItemsCreated:
                        ITHit.Events.AddListener(this, sEventName, fCallback, oContext);
                        break;

                    default:
                        throw new ITHit.WebDAV.Client.Exceptions.WebDavException('Not found event name `' + sEventName + '`');
                }
            },

            /**
             * Removes event listener.
             * @api
             * @param {string} sEventName The event name to remove.
             * @param {Function} fCallback The callback to remove.
             * @param {Object} [oContext] The context to callback is called with.
             */
            RemoveListener: function(sEventName, fCallback, oContext) {
                ITHit.Events.RemoveListener(this, sEventName, fCallback, oContext);
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated~Result} oResult
             */
            _OnUploadItemsCreatedAsyncDispatched: function(oResult) {
                if (oResult.Upload) {
                    this.AddRange(oResult.Upload);
                    return;
                }

                this._OnUploadItemsCreatedAsyncDispatchedDeprecated(oResult);
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated~Result} oResult
             */
            _OnUploadItemsCreatedAsyncDispatchedDeprecated: function(oResult) {
                var aNotSkippedItems = this._FilterSkippedItems(oResult);
                var oOverwriteMap = this._CreateUrlUploadItemMap(oResult.Overwrite);
                aNotSkippedItems.forEach(function(oItem) {
                    if (oOverwriteMap.Has(oItem.GetUrl())) oItem.SetOverwrite(true);
                });

                this.AddRange(aNotSkippedItems);
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.Upload.Events.UploadItemsCreated~Result} oResult
             * @return {ITHit.WebDAV.Client.Upload.UploadItem[]}
             */
            _FilterSkippedItems: function(oResult) {
                var oSkippedMap = this._CreateUrlUploadItemMap(oResult.Skip);
                return oResult.Original.filter(function(oItem) {
                    return !oSkippedMap.Has(oItem.GetUrl());
                })
            },

            /**
             * @private
             * @param {ITHit.WebDAV.Client.Upload.UploadItem[]} aItems
             * @return {ITHit.WebDAV.Client.Upload.Collections.Map<ITHit.WebDAV.Client.Upload.UploadItem>}
             */
            _CreateUrlUploadItemMap: function(aItems) {
                /** @type {ITHit.WebDAV.Client.Upload.Collections.Map<ITHit.WebDAV.Client.Upload.UploadItem>} */
                var oMap = new ITHit.WebDAV.Client.Upload.Collections.Map();
                aItems.forEach(function(oItem) {
                    oMap.Set(oItem.GetUrl(), oItem);
                });

                return oMap;
            },

            /**
             * @private
             * @readonly
             * @type {ITHit.WebDAV.Client.Upload.Groups.GroupManager}
             */
            _GroupManager: null
        });
})();


(function() {
    'use strict';

    /**
     * Instance of this class store drop zones and provide methods to creating
     * and removing them
     * @api
     * @class ITHit.WebDAV.Client.Upload.DropZoneCollection
     */
    var staticSelf = ITHit.DefineClass('ITHit.WebDAV.Client.Upload.DropZoneCollection',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.DropZoneCollection.prototype */
        {

            /**
             * @private
             * @type {Object.<string, ITHit.WebDAV.Client.Upload.Controls.DropZone>}
             */
            _UnderlyingSet: null,

            /**
             * @api
             * @type {ITHit.WebDAV.Client.Upload.Uploader}
             */
            Uploader: null,

            constructor: function(oUploader) {
                this._Uploader = oUploader;
                this._UnderlyingSet = {};
            },

            /**
             * Bind HTML element as drop zone.
             * @api
             * @example
             *  &lt;!DOCTYPE html&gt;
             *  &lt;html&gt;
             *  &lt;head&gt;
             *      &lt;script type="text/javascript"&gt;
             *              var oUploader = new ITHit.WebDAV.Client.Upload.Uploader();
             *              oUploader.DropZones.AddById('ithit-dropzone');
             *      &lt;/script&gt;
             *  &lt;/head&gt;
             *  &lt;body
             *      &lt;div id="ithit-dropzone"&gt;
             *          Drop file to upload&lt;
             *      &lt;/div&gt;
             *  &lt;/body&gt;
             *  &lt;/html&gt;
             * @param {string} sElementId Id of HTML element.
             * @return {ITHit.WebDAV.Client.Upload.Controls.DropZone} Created drop zone.
             */
            AddById: function(sElementId) {
                var oExists = this.GetById(sElementId);
                if (oExists) {
                    return oExists;
                }

                var oDropZone = new ITHit.WebDAV.Client.Upload.Controls.DropZone(sElementId);
                this._UnderlyingSet[sElementId] = oDropZone;
                this._RaiseOnCollectionChanged([oDropZone], []);
                return oDropZone;
            },

            /**
             * Get drop zone by Id.
             * @api
             * @param {string} sElementId Id of HTML element.
             * @return {(ITHit.WebDAV.Client.Upload.Controls.DropZone | undefined)} Found drop zone or undefined.
             */
            GetById: function(sElementId) {
                return this._UnderlyingSet[sElementId];
            },

            /**
             * Remove HTML element from drop zone Controls by id.
             * @api
             * @param {string} sElementId Id of HTML element.
             */
            RemoveById: function(sElementId) {
                var oDropZone = this.GetById(sElementId);
                if (oDropZone) {
                    delete this._UnderlyingSet[sElementId];
                    this._RaiseOnCollectionChanged([], [oDropZone]);
                }
            },

            /**
             * Add event handlers.
             * @public
             * @param {string} sEventName The event name to handle.
             * @param {Function} fCallback The callback to call.
             * @param {Object} [oContext] The context to callback is called with.
             */
            AddListener: function(sEventName, fCallback, oContext) {
                oContext = oContext || null;
                this._CheckEventNameOtThrow(sEventName);
                ITHit.Events.AddListener(this, sEventName, fCallback, oContext);
            },

            /**
             * Removes event listener.
             * @public
             * @param {string} sEventName The event name to remove.
             * @param {Function} fCallback The callback to remove.
             * @param {Object} [oContext] The context to callback is called with.
             */
            RemoveListener: function(sEventName, fCallback, oContext) {
                oContext = oContext || null;
                this._CheckEventNameOtThrow(sEventName);
                ITHit.Events.RemoveListener(this, sEventName, fCallback, oContext);
            },


            _CheckEventNameOtThrow: function(sEventName) {
                if (sEventName !== staticSelf.EVENT_ON_COLLECTION_CHANGED) {
                    throw new ITHit.WebDAV.Client.Exceptions.NotFoundEventNameException(sEventName);
                }
            },

            /**
             * @private
             * @param {(ITHit.WebDAV.Client.Upload.Controls.DropZone[] | null)} aAdded
             * @param {(ITHit.WebDAV.Client.Upload.Controls.DropZone[] | null)} aRemoved
             */
            _RaiseOnCollectionChanged: function(aAdded, aRemoved) {
                ITHit.Events.DispatchEvent(this, staticSelf.EVENT_ON_COLLECTION_CHANGED, [{
                    Sender: this,
                    AddedItems: aAdded || [],
                    RemovedItems : aRemoved || []
                }]);
            }
        },
        /** @lends ITHit.WebDAV.Client.Upload.DropZoneCollection */
        {
            /**
             * Event reporting that collection changed. Fired when item is added or deleted from collection.
             * @public
             * @event ITHit.WebDAV.Client.Upload.DropZoneCollection#OnCollectionChanged
             * @property {ITHit.WebDAV.Client.Upload.DropZoneCollection} Sender The collection instance.
             * @property {ITHit.WebDAV.Client.Upload.Controls.DropZone[]} AddedItems Added items.
             * @property {ITHit.WebDAV.Client.Upload.Controls.DropZone[]} RemovedItems Removed items.
             */
            EVENT_ON_COLLECTION_CHANGED: 'OnCollectionChanged'
        });
})();


(function() {
    /**
     * List of upload inputs. Contains items of {@link ITHit.WebDAV.Client.Upload.Controls.Input}  type.
     * @api
     * @class ITHit.WebDAV.Client.Upload.InputCollection
     */
    var staticSelf = ITHit.DefineClass('ITHit.WebDAV.Client.Upload.InputCollection',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.InputCollection.prototype */{

            /**
             * @private
             * @type {Object.<string, ITHit.WebDAV.Client.Upload.Controls.Input>}
             */
            _UnderlyingSet: null,

            /**
             * @api
             * @type {ITHit.WebDAV.Client.Upload.Uploader}
             */
            Uploader: null,
            constructor: function(oUploader) {
                this._UnderlyingArray = [];
                this._Uploader = oUploader;
            },

            /**
             * Bind HTML element as input.
             * @api
             * @example
             *  &lt;!DOCTYPE html&gt;
             *  &lt;html&gt;
             *  &lt;head&gt;
             *      &lt;script type="text/javascript"&gt;
             *              var oUploader = new ITHit.WebDAV.Client.Upload.Uploader();
             *              oUploader.Inputs.AddById('ithit-input');
             *      &lt;/script&gt;
             *  &lt;/head&gt;
             *  &lt;body
             *      &lt;input id="ithit-input" type="file"&gt;
             *  &lt;/body&gt;
             *  &lt;/html&gt;
             * @param {string} sElementId Id of HTML element.
             * @return {ITHit.WebDAV.Client.Upload.Controls.Input} Created input object.
             */
            AddById: function(sElementId) {
                var oInput = new ITHit.WebDAV.Client.Upload.Controls.Input(sElementId);
                this._UnderlyingArray[sElementId] = oInput;
                this._RaiseOnCollectionChanged([oInput], []);
                return oInput;
            },

            /**
             * Get input object by Id.
             * @api
             * @param {string} sElementId Id of HTML element.
             * @return {ITHit.WebDAV.Client.Upload.Controls.Input | undefined} Founded input or undefined.
             */
            GetById: function(sElementId) {
                return this._UnderlyingArray[sElementId];
            },

            /**
             * Remove HTML element from input Controls by id.
             * @api
             * @param {string} sElementId Id of HTML element.
             */
            RemoveById: function(sElementId) {
                var oInput = this.GetById(sElementId);
                if (oInput) {
                    delete this._UnderlyingSet[sElementId];
                    this._RaiseOnCollectionChanged([], [oInput]);
                }
            },

            /**
             * Add event handlers.
             * @public
             * @param {string} sEventName The event name to handle.
             * @param {Function} fCallback The callback to call.
             * @param {Object} [oContext] The context to callback is called with.
             */
            AddListener: function(sEventName, fCallback, oContext) {
                oContext = oContext || null;
                this._CheckEventNameOtThrow(sEventName);
                ITHit.Events.AddListener(this, sEventName, fCallback, oContext);
            },

            /**
             * Removes event listener.
             * @public
             * @param {string} sEventName The event name to remove.
             * @param {Function} fCallback The callback to remove.
             * @param {Object} [oContext] The context to callback is called with.
             */
            RemoveListener: function(sEventName, fCallback, oContext) {
                oContext = oContext || null;
                this._CheckEventNameOtThrow(sEventName);
                ITHit.Events.RemoveListener(this, sEventName, fCallback, oContext);
            },


            _CheckEventNameOtThrow: function(sEventName) {
                if (sEventName !== staticSelf.EVENT_ON_COLLECTION_CHANGED) {
                    throw new ITHit.WebDAV.Client.Exceptions.NotFoundEventNameException(sEventName);
                }
            },

            /**
             * @private
             * @param {(ITHit.WebDAV.Client.Upload.Controls.Input[] | null)} aAdded
             * @param {(ITHit.WebDAV.Client.Upload.Controls.Input[] | null)} aRemoved
             */
            _RaiseOnCollectionChanged: function(aAdded, aRemoved) {
                ITHit.Events.DispatchEvent(this, staticSelf.EVENT_ON_COLLECTION_CHANGED, [{
                    Sender: this,
                    AddedItems: aAdded || [],
                    RemovedItems: aRemoved || []
                }]);
            }
        },
        /** @lends ITHit.WebDAV.Client.Upload.InputCollection */
        {
            /**
             * Event reporting that collection changed. Fired when item is added or deleted from collection.
             * @public
             * @event ITHit.WebDAV.Client.Upload.InputCollection#OnCollectionChanged
             * @property {ITHit.WebDAV.Client.Upload.InputCollection} Sender The collection instance.
             * @property {ITHit.WebDAV.Client.Upload.Controls.Input[]} AddedItems Added items.
             * @property {ITHit.WebDAV.Client.Upload.Controls.Input[]} RemovedItems Removed items.
             */
            EVENT_ON_COLLECTION_CHANGED: 'OnCollectionChanged'
        });
})();



(function() {
    'use strict';
    ITHit.DefineClass('ITHit.WebDAV.Client.Upload.Uploader',
        null,
        /** @lends ITHit.WebDAV.Client.Upload.Uploader.prototype */ {

            /**
             * Collection of associated drop zones.
             * @api
             * @readonly
             * @type { ITHit.WebDAV.Client.Upload.DropZoneCollection }
             */
            DropZones: null,
            /**
             * Collection of associated inputs.
             * @api
             * @readonly
             * @type { ITHit.WebDAV.Client.Upload.InputCollection }
             */
            Inputs: null,
            /**
             * Queue of uploads.
             * @api
             * @readonly
             * @type {ITHit.WebDAV.Client.Upload.Queue}
             */
            Queue: null,

            /**
             * Default settings for uploads.
             * @api
             * @type { ITHit.WebDAV.Client.Upload.Settings }
             */
            Settings: null,

            /**
             * @type {ITHit.WebDAV.Client.Upload.Providers.UploadProvider}
             */
            _UploadProvider: null,

            /**
             * Create uploader instance.
             * @example
             *  &lt;!DOCTYPE html&gt;
             *  &lt;html lang="en"&gt;
             *  &lt;head&gt;
             *      &lt;title&gt;IT Hit WebDAV Uploader&lt;/title&gt;
             *      &lt;script src="ITHitWebDAVClient.js" type="text/javascript"&gt;&lt;/script&gt;
             *      &lt;link href="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet"&gt;
             *      &lt;script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.1.0/jquery.min.js"&gt;&lt;/script&gt;
             *      &lt;script type="text/javascript"&gt;
             *          function UploaderGridView(sSelector) {
             *              this.Uploader = new ITHit.WebDAV.Client.Upload.Uploader();
             *              this.Uploader.DropZones.AddById('ithit-dropzone');
             *              this.Uploader = oUploader;
             *              this.Uploader.Queue.AddListener('OnQueueChanged', '_CollectionChange', this);
             *              this.$table = $(sSelector);
             *              this.rows = [];
             *          };
             *
             *          /&#x002A&#x002A
             *          * Observes adding and deleting of UploadItem and creates and removes rows in table.
             *          * @param {ITHit.WebDAV.Client.Upload.Queue#OnQueueChanged} oQueueChanged
             *          &#x002A/
             *          UploaderGridView.prototype._CollectionChange = function(oQueueChanged) {
             *              $.each(oQueueChanged.AddedItems, function(index, value) {
             *                  var row = new UploaderGridRow(value);
             *                  this.rows.push(row);
             *                  this.$table.append(row.$el);
             *              }.bind(this));
             *
             *              $.each(oQueueChanged.RemovedItems, function(index, value) {
             *                  var aRows = $.grep(this.rows, function(oElem) { return value === oElem.UploadItem; });
             *                  var iIndex = this.rows.indexOf(aRows[0]);
             *                  this.rows.splice(iIndex, 1);
             *                  aRows[0].$el.remove();
             *              }.bind(this));
             *          };
             *
             *          /&#x002A&#x002A
             *          * Represents table row and subscribes for upload change.
             *          * @param {ITHit.WebDAV.Client.Upload.oUploadItem} oUploadItem
             *          &#x002A/
             *          function UploaderGridRow(oUploadItem) {
             *              this.$el = $('<tr></tr>');
             *              this.oUploadItem = oUploadItem;
             *              this.oUploadItem.AddListener('OnProgressChanged', '_OnProgress', this);
             *              this.oUploadItem.AddListener('OnStateChanged', '_OnStateChange', this);
             *              this._Render(oUploadItem);
             *          };
             *
             *
             *          /&#x002A&#x002A
             *          * Creates upload details view.
             *          * @param {ITHit.WebDAV.Client.Upload.oUploadItem} oUploadItem
             *          &#x002A/
             *          UploaderGridRow.prototype._Render = function(oUploadItem) {
             *          /&#x002A&#x002A @typedef {ITHit.WebDAV.Client.Upload.Progress} oProgress &#x002A/
             *              var oProgress = oUploadItem.GetProgress();
             *              var columns = [
             *                  oUploadItem.GetName(),
             *                  oUploadItem.GetUrl(),
             *                  oUploadItem.GetSize(),
             *                  oProgress.UploadedBytes,
             *                  oProgress.Completed,
             *                  oProgress.ElapsedTime,
             *                  oProgress.RemainingTime,
             *                  oProgress.Speed,
             *                  oUploadItem.GetState()
             *              ];
             *
             *              var $columns = [];
             *              columns.forEach(function(item) {
             *                  var $column = $('&lt;td&gt;&lt;/td&gt;');
             *                  $column.html(item);
             *                  $columns.push($column);
             *              });
             *
             *              var $actions = $('&lt;td&gt;&lt;/td&gt;');
             *              this._RenderActions(oUploadItem).forEach(function(item) {
             *                  $actions.append(item);
             *              });
             *
             *              $columns.push($actions);
             *              this.$el.empty();
             *              this.$el.append($columns);
             *          };
             *
             *          /&#x002A&#x002A
             *          * Creates upload actions view.
             *          * @param {ITHit.WebDAV.Client.Upload.oUploadItem} oUploadItem
             *          &#x002A/
             *          UploaderGridRow.prototype._RenderActions = function(oUploadItem) {
             *              var actions = [];
             *              actions.push($('&lt;a&gt;&lt;/a&gt;').
             *                  html('&lt;span class="glyphicon glyphicon-play"&gt;&lt;/span&gt;').
             *                  attr('href', 'javascript:void(0)').
             *                  on('click', oUploadItem.StartAsync.bind(oUploadItem)));
             *
             *              actions.push($('&lt;a&gt;&lt;/a&gt;').
             *                  html('&lt;span class="glyphicon glyphicon-stop"&gt;&lt;/span&gt;').
             *                  attr('href', 'javascript:void(0)').
             *                  on('click',oUploadItem.CancelAsync.bind(oUploadItem)));
             *          };
             *
             *          /&#x002A&#x002A
             *          * Handles UploadItem state change.
             *          * @param {ITHit.WebDAV.Client.Upload.UploadItem#OnStateChanged} oStateChangedEvent
             *          &#x002A/
             *          UploaderGridRow.prototype._OnStateChange = function(oStateChangedEvent) {
             *              this._Render(oStateChangedEvent.Sender);
             *          };
             *
             *          /&#x002A&#x002A
             *          * Handles UploadItem progress change.
             *          * @param {ITHit.WebDAV.Client.Upload.UploadItem#OnProgressChanged} oProgressEvent
             *          &#x002A/
             *          UploaderGridRow.prototype._OnProgress = function(oProgressEvent) {
             *              this._Render(oProgressEvent.Sender);
             *          };
             *
             *          var sUploadUrl = 'https://webdavserver/path/';
             *          var oUploaderGrid = new UploaderGridView(oUploader, '.ithit-grid-uploads');
             *          oUploaderGrid.Uploader.SetUploadUrl(sUploadUrl);
             *      &lt;/script&gt;
             *  &lt;/head&gt;
             *  &lt;body id="it-hit-dropzone"&gt;
             *      &lt;table class="table table-responsive ithit-grid-uploads"&gt;
             *          &lt;thead&gt;
             *              &lt;tr&gt;
             *                  &lt;th&gt;Display Name&lt;/th&gt;
             *                  &lt;th&gt;Download Url&lt;/th&gt;
             *                  &lt;th&gt;Size&lt;/th&gt;
             *                  &lt;th&gt;Uploaded Bytes&lt;/th&gt;
             *                  &lt;th&gt;Completed&lt;/th&gt;
             *                  &lt;th&gt;Elapsed TimeSpan&lt;/th&gt;
             *                  &lt;th&gt;Remaining TimeSpan&lt;/th&gt;
             *                  &lt;th&gt;Speed&lt;/th&gt;
             *                  &lt;th&gt;State&lt;/th&gt;
             *                  &lt;th&gt;Actions&lt;/th&gt;
             *              &lt;/tr&gt;
             *          &lt;/thead&gt;
             *          &lt;tbody&gt;
             *          &lt;/tbody&gt;
             *      &lt;/table&gt;
             *  &lt;/body&gt;
             *  &lt;/html&gt;
             * @classdesc This class provides methods for managing file drop
             * zones, inputs and upload queue.
             * @api
             * @class ITHit.WebDAV.Client.Upload.Uploader
             * @constructs
             */
            constructor: function() {
                this.Inputs = new ITHit.WebDAV.Client.Upload.InputCollection(this);
                this.Inputs.AddListener(ITHit.WebDAV.Client.Upload.InputCollection.EVENT_ON_COLLECTION_CHANGED , this._OnControlCollectionChangedEventHandler, this);
                this.DropZones = new ITHit.WebDAV.Client.Upload.DropZoneCollection(this);
                this.DropZones.AddListener(ITHit.WebDAV.Client.Upload.DropZoneCollection.EVENT_ON_COLLECTION_CHANGED , this._OnControlCollectionChangedEventHandler, this);
                this.Settings = new ITHit.WebDAV.Client.Upload.Settings();
                this.Queue = new ITHit.WebDAV.Client.Upload.Queue(this);
            },

            /**
             * Set upload url for drop zones and inputs.
             * @api
             * @param {string} sUrl Url to upload.
             */
            SetUploadUrl: function(sUrl) {
                this._UploadUrl = sUrl;
            },

            /**
             * Get upload url for drop zones and inputs.
             * @api
             * @return {string} Upload url.
             */
            GetUploadUrl: function() {
                return this._UploadUrl;
            },

            /**
             * @param {(ITHit.WebDAV.Client.Upload.InputCollection#event:OnCollectionChanged | ITHit.WebDAV.Client.Upload.DropZoneCollection#event:OnCollectionChanged)} oOnCollectionChanged
             */
            _OnControlCollectionChangedEventHandler:function (oOnCollectionChanged) {
                oOnCollectionChanged.AddedItems.forEach(function(oItem){
                    oItem.AddListener(ITHit.WebDAV.Client.Upload.Controls.HtmlControl.EVENT_ON_FILE_INPUT_HANDLED, this._OnFileInputEventHandler.bind(this));
                }.bind(this));

                oOnCollectionChanged.RemovedItems.forEach(function(oItem){
                    oItem.RemoveListener(ITHit.WebDAV.Client.Upload.Controls.HtmlControl.EVENT_ON_FILE_INPUT_HANDLED, this._OnFileInputEventHandler.bind(this));
                }.bind(this));
            },

            /**
             * @param {ITHit.WebDAV.Client.Upload.Controls.HtmlControl#event:OnFileInputHandled} oOnFileInputHandled
             */
            _OnFileInputEventHandler:function (oOnFileInputHandled) {
               this.Queue.AddGroup(this._UploadUrl, oOnFileInputHandled.AsyncResult.Result, oOnFileInputHandled.Source);
            }
        });
})();


// Clear temporary variable.
ITHit.Temp = {};
