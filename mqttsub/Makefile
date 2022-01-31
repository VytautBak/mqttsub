include $(TOPDIR)/rules.mk

PKG_NAME:=mqttsub
PKG_RELEASE:=1
PKG_VERSION:=1.0.0

include $(INCLUDE_DIR)/package.mk

define Package/mqttsub
	CATEGORY:=Base system
	TITLE:=mqttsub
	DEPENDS:=+libopenssl +libmosquitto +libuci +libcurl
endef

define Package/mqttsub/description
	Listens to MQTT messages and executes user configured events
endef

define Package/mqttsub/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/etc/rc.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mqttsub $(1)/usr/bin
	$(INSTALL_BIN) ./files/mqttsub.init $(1)/etc/init.d/mqttsub
	$(INSTALL_CONF) ./files/mqttsub.config $(1)/etc/config/mqttsub
	ln -s /etc/init.d/mqttsub $(1)/etc/rc.d/S99mqttsub
endef

$(eval $(call BuildPackage,mqttsub))
