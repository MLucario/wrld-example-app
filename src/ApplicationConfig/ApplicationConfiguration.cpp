// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        ApplicationConfiguration::ApplicationConfiguration(const std::string& name,
                                                           const std::string& eegeoApiKey,
                                                           const Eegeo::Space::LatLongAltitude& interestLocation,
                                                           float distanceToInterestMetres,
                                                           float orientationDegrees,
                                                           bool tryStartAtGpsLocation,
                                                           bool startFullscreen,
                                                           const std::string& googleAnalyticsReferrerToken,
                                                           const std::string& flurryAppKey,
                                                           const std::string& yelpConsumerKey,
                                                           const std::string& yelpConsumerSecret,
                                                           const std::string& yelpOAuthToken,
                                                           const std::string& yelpOAuthTokenSecret,
                                                           const std::string& geoNamesUserName,
                                                           const std::string& coverageTreeManifestURL,
                                                           const std::string& themeManifestURL,
                                                           const std::string& sqliteDbUrl,
                                                           const std::string& searchServiceUrl,
                                                           const std::string& myPinsWebServiceUrl,
                                                           const std::string& myPinsWebServiceAuthToken,
                                                           const std::string& productVersion,
                                                           const std::string& buildNumber,
                                                           const std::string& combinedVersionString,
                                                           bool webProxyEnabled,
                                                           const std::string& webProxyIpAddress,
                                                           int webProxyPort,
                                                           const std::string& webProxyIgnorePattern,
                                                           const std::string& senionMapKey,
                                                           const std::string& senionMapCustomerID,
                                                           const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>& buildingsInfo,
                                                           const bool isKioskTouchInputEnabled)
        : m_name(name)
        , m_eegeoApiKey(eegeoApiKey)
        , m_interestLocation(interestLocation)
        , m_distanceToInterestMetres(distanceToInterestMetres)
        , m_orientationDegrees(orientationDegrees)
        , m_tryStartAtGpsLocation(tryStartAtGpsLocation)
        , m_shouldStartFullscreen(startFullscreen)
        , m_googleAnalyticsReferrerToken(googleAnalyticsReferrerToken)
        , m_flurryAppKey(flurryAppKey)
        , m_yelpConsumerKey(yelpConsumerKey)
        , m_yelpConsumerSecret(yelpConsumerSecret)
        , m_yelpOAuthToken(yelpOAuthToken)
        , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
        , m_geoNamesUserName(geoNamesUserName)
        , m_coverageTreeManifestURL(coverageTreeManifestURL)
        , m_themeManifestURL(themeManifestURL)
        , m_sqliteDbUrl(sqliteDbUrl)
        , m_searchServiceUrl(searchServiceUrl)
        , m_myPinsWebServiceUrl(myPinsWebServiceUrl)
        , m_myPinsWebServiceAuthToken(myPinsWebServiceAuthToken)
        , m_productVersion(productVersion)
        , m_buildNumber(buildNumber)
        , m_combinedVersionString(combinedVersionString)
        , m_webProxyEnabled(webProxyEnabled)
        , m_webProxyIpAddress(webProxyIpAddress)
        , m_webProxyPort(webProxyPort)
        , m_webProxyIgnorePattern(webProxyIgnorePattern)
        , m_senionMapKey(senionMapKey)
        , m_senionMapCustomerID(senionMapCustomerID)
        , m_buildingsInfo(buildingsInfo)
        , m_isKioskTouchInputEnabled(isKioskTouchInputEnabled)
        {
            
        }
        
        const std::string& ApplicationConfiguration::Name() const
        {
            return m_name;
        }
        
        const std::string& ApplicationConfiguration::EegeoApiKey() const
        {
            return m_eegeoApiKey;
        }
        
        const Eegeo::Space::LatLongAltitude& ApplicationConfiguration::InterestLocation() const
        {
            return m_interestLocation;
        }
        
        float ApplicationConfiguration::DistanceToInterestMetres() const
        {
            return m_distanceToInterestMetres;
        }
        
        float ApplicationConfiguration::OrientationDegrees() const
        {
            return m_orientationDegrees;
        }
        
        bool ApplicationConfiguration::TryStartAtGpsLocation() const
        {
            return m_tryStartAtGpsLocation;
        }
        
        const std::string& ApplicationConfiguration::GoogleAnalyticsReferrerToken() const
        {
            return m_googleAnalyticsReferrerToken;
        }
        
        const std::string& ApplicationConfiguration::FlurryAppKey() const
        {
            return m_flurryAppKey;
        }
        
        const std::string& ApplicationConfiguration::YelpConsumerKey() const
        {
            return m_yelpConsumerKey;
        }
        
        const std::string& ApplicationConfiguration::YelpConsumerSecret() const
        {
            return m_yelpConsumerSecret;
        }
        
        const std::string& ApplicationConfiguration::YelpOAuthToken() const
        {
            return m_yelpOAuthToken;
        }
        
        const std::string& ApplicationConfiguration::YelpOAuthTokenSecret() const
        {
            return m_yelpOAuthTokenSecret;
        }
        
        const std::string& ApplicationConfiguration::GeoNamesUserName() const
        {
            return m_geoNamesUserName;
        }
        
        const std::string& ApplicationConfiguration::CoverageTreeManifestURL() const
        {
            return m_coverageTreeManifestURL;
        }
        
        const std::string& ApplicationConfiguration::ThemeManifestURL() const
        {
            return m_themeManifestURL;
        }
        
        const std::string& ApplicationConfiguration::SqliteDbUrl() const
        {
            return m_sqliteDbUrl;
        }
        
        const std::string& ApplicationConfiguration::SearchServiceUrl() const
        {
            return m_searchServiceUrl;
        }

        const std::string& ApplicationConfiguration::MyPinsWebServiceUrl() const
        {
            return m_myPinsWebServiceUrl;
        }
        
        const std::string& ApplicationConfiguration::MyPinsWebServiceAuthToken() const
        {
            return m_myPinsWebServiceAuthToken;
        }

        const std::string& ApplicationConfiguration::ProductVersion() const
        {
            return m_productVersion;
        }
        
        const std::string& ApplicationConfiguration::BuildNumber() const
        {
            return m_buildNumber;
        }
        
        const std::string& ApplicationConfiguration::CombinedVersionString() const
        {
            return m_combinedVersionString;
        }
        
        bool ApplicationConfiguration::WebProxyEnabled() const
        {
            return m_webProxyEnabled;
        }
        
        const std::string& ApplicationConfiguration::WebProxyIpAddress() const
        {
            return m_webProxyIpAddress;
        }
        
        int ApplicationConfiguration::WebProxyPort() const
        {
            return m_webProxyPort;
        }

        const std::string& ApplicationConfiguration::WebProxyIgnorePattern() const
        {
            return m_webProxyIgnorePattern;
        }
        
        const std::string& ApplicationConfiguration::SenionMapKey() const{
            return m_senionMapKey;
        }
        
        const std::string& ApplicationConfiguration::SenionMapCustomerID() const{
            return m_senionMapCustomerID;
        }
        
        
        const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>& ApplicationConfiguration::BuildingsInfo() const{
            return m_buildingsInfo;
        }

        bool ApplicationConfiguration::IsKioskTouchInputEnabled() const
        {
            return m_isKioskTouchInputEnabled;
        }

        bool ApplicationConfiguration::ShouldStartFullscreen() const
        {
            return m_shouldStartFullscreen;
        }

    }
}
