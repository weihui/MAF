/*
 *  mafNetworkConnectorQtSoap.h
 *  mafEventBus
 *
 *  Created by Daniele Giunchi on 14/07/10.
 *  Copyright 2009-2011 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFNETWORKCONNECTORQTSOAP_H
#define MAFNETWORKCONNECTORQTSOAP_H

// include list
#include "mafNetworkConnector.h"

// Foundation Library include list
#include <qtsoap.h>

namespace mafEventBus {

/**
 Class name: mafNetworkConnectorQtSoap
 This class is the implementation class for client/server objects that works over network
 with soap protocol. It has been implemented only client side.
 */
class MAFEVENTBUSSHARED_EXPORT mafNetworkConnectorQtSoap : public mafNetworkConnector {
    Q_OBJECT

public:
    /// object constructor.
    mafNetworkConnectorQtSoap();

    /// object destructor.
    /*virtual*/ ~mafNetworkConnectorQtSoap();

    /// create the unique instance of the client.
    /*virtual*/ void createClient(const QString hostName, const unsigned int port, QMap<QString,QVariant> *advancedParameters = NULL );

	/// Set advanced parameters
	/* REQUIRE(advancedParameters->contains("Action")) 
	REQUIRE(advancedParameters->contains("WSDLUrl"))	
	REQUIRE(advancedParameters->contains("Path")) */
    /*virtual*/ void setAdvancedParameters(QMap<QString, QVariant> *advancedParameters);

    /// create the unique instance of the server.
    /*virtual*/ void createServer(const unsigned int port);

    /// Start the server.
    /*virtual*/ void startListen();

    /// Allow to send a network request.
    /** Need to convert the parameter list into another list of basic type to string which are used in QtSoap.*/
    /*virtual*/ void send(const QString methodName, mafEventArgumentsList *argList, bool externalSend = false);

	/// return the response retrieved from the service
    QtSoapType *response();

    /// register all the signalsand slots
    /*virtual*/ void initializeForEventBus();

    //retrieve an instance of the object
    virtual mafNetworkConnector *clone();

Q_SIGNALS:
    /// signal for the registration of the functions with parameters
    void registerMethodsServer(mafRegisterMethodsMap registerMethodsList);

public Q_SLOTS:
    /// register methods on the server
    void registerServerMethod(QString methodName, QList<QVariant::Type> types);

private Q_SLOTS:
    
	/// retrieve response from the service
    void retrieveRemoteResponse();

private:
    /// Marshalling of the datatypes
    QtSoapType *marshall(const QString name, const QVariant &parameter);

	/// Unmarshalling of the qtsoap datatypes
	QVariant unmarshall(QtSoapType *s );

	/// stop and destroy the server instance.
    void stopServer();

	///Add a custom string header to the qtsoap envelope message using the m_AuthenticationMap attribute
	void addAuthenticationHeader();

	QtSoapHttpTransport *m_Http; ///< variable that represents the soap request from client to server
    QtSoapMessage m_Request; ///< variable that represents the request
    mafRegisterMethodsMap m_RegisterMethodsMap;
    QString m_WSDLUrl; ///< represents the url of the wsdl
    QString m_Action; ///< represents the action to put inside transport http
    QString m_Path; ///< represents the path (for example the endpoint)
    QtSoapType *m_Response;
	bool m_SecureConnection;
};

/////////////////////////////////////////////////////////////
// Inline methods
/////////////////////////////////////////////////////////////

inline QtSoapType *mafNetworkConnectorQtSoap::response() {
    return m_Response;
}


} //namespace mafEventBus

#endif // MAFNETWORKCONNECTORQTSOAP_H
