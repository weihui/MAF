/*
 *  mafDataSet.h
 *  mafResources
 *
 *  Created by Paolo Quadrani on 30/12/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFDATASET_H
#define MAFDATASET_H

// Includes list
#include "mafResourcesDefinitions.h"
#include "mafMementoDataSet.h"
#include <mafProxyInterface.h>

namespace mafResources {

// Class forwarding list
class mafDataBoundaryAlgorithm;

/**
 Class name: mafDataSet
 This is the base class for the MAF3 DataSet.
 It provides also 2 signals for data connected and disconnected.
 Each time that someone connect externally some data a dataValueConnected signal is emitted.
 When the external data is deleted or removed manually, a dataValueDisconnected has been emitted.
 */
class MAFRESOURCESSHARED_EXPORT mafDataSet : public mafCore::mafObject {
    Q_OBJECT
    Q_PROPERTY(QString externalDataType READ externalDataType WRITE setExternalDataType)
    Q_PROPERTY(QString boundaryAlgorithmName READ boundaryAlgorithmName WRITE setBoundaryAlgorithmName)
    Q_PROPERTY(QVariantList bounds READ bounds WRITE setBounds)

    /// typedef macro.
    mafSuperclassMacro(mafCore::mafObject);

signals:
    /// Signal emitted when data value has been added to the mafDataSet.
    void dataValueConnected();
    /// Signal emitted when data value has been removed from mafDataSet.
    void dataValueDisconnected();

public:
    /// Object constructor.
    mafDataSet(const QString code_location = "");

    /// Return the data boundary.
    mafCore::mafProxyInterface *dataBoundary();

    /// Return the data value contained into the dataset.
    mafCore::mafProxyInterface *dataValue();

    /// Assign the given data value to the dataset.
    void setDataValue(mafCore::mafProxyInterface *data_value);

    /// Set the pose for the current data.
    void setPoseMatrix(const mafPoseMatrix *matrix);

    /// Return the pose matrix of the current data.
    mafPoseMatrix *poseMatrix() const;

    /// Set the boundary algorithm function to be used to calculate the data value boundary according also to its pose matrix.
    void setBoundaryAlgorithm(mafDataBoundaryAlgorithm *algorithm);

    /// Return the boundary algorithm function used to calculate the data value boundary
    mafDataBoundaryAlgorithm *boundaryAlgorithm() const;

    /// Set the name of mafDataBoundaryAlgorithm.
    void setBoundaryAlgorithmName(QString dataBoundaryAlgorithmName);

    /// Return the name of mafDataBoundaryAlgorithm;
    QString boundaryAlgorithmName() const;

    /// Set the bounds of the bounding box of the VME.
    void setBounds(QVariantList bounds);

    /// Return the bounds of the bounding box of the VME.
    QVariantList bounds();

    /// Update bounds of the bounding box.
    /*virtual*/ void updateBounds();

    /// Return the instance of the resource's status. The caller has to delete the allocated memory he asked.
    /*virtual*/ mafCore::mafMemento *createMemento() const;

    /// Allows setting a previous saved object's state.
    /**
     This is used to implement a sort of undo mechanism for the object's state, but can be used also by the
    serialization mechanism to serialize data into the selected storage type.
    The 'deep_memento' flag is used to avoid the copy of the object unique hash in normal operation like
    undo or copy/paste operations. The complete object save is instead needed for serialization pourposes.*/
    /*virtual*/ void setMemento(mafCore::mafMemento *memento, bool deep_memento = false);

    /// Load external data and fill the mafDataSet.
    void updateDataValue();

    /// Return type of data contained in the mafDataSet.
    QString externalDataType() const; 

    /// Set type of data contained in the mafDataSet.
    void setExternalDataType(QString externalDataType);

    /// Return true if data has been loaded.
    bool dataLoaded() const;

protected:
    /// Object destructor.
    /* virtual */ ~mafDataSet();

private:
    mafCore::mafProxyInterface *m_DataValue; ///< Data value present into the current dataset at current timestamp.
    mafCore::mafProxyInterface *m_DataBoundary; ///< Represent the boundary of current data value at current timestamp.
    mafPoseMatrix *m_Matrix; ///< Pose matrix
    mafDataBoundaryAlgorithm *m_DataBoundaryAlgorithm; ///< Represent the class that will calculate the boundary of the m_DataValue and generate as output a boundary to be visualized.
    QString m_DataBoundaryAlgorithmName; ///< Name of the mafDataBoundaryAlgorithm.
    QString m_ExternalDataType; ///< Type of data contained in the mafDataSet.
    bool m_DataLoaded; ///< Set true when data is loaded in memory.
    QVariantList m_Bounds; ///< List of bounds value of the binding box.

    struct dataFileInfo {
      QString fileName;            ///< Name of the file containing the datat.
      QString encodeType;     ///< encode to be used to decode data.
    } m_DataFileInfo; 

};

/////////////////////////////////////////////////////////////
// Inline methods
/////////////////////////////////////////////////////////////

inline mafPoseMatrix *mafDataSet::poseMatrix() const {
    return m_Matrix;
}

inline mafDataBoundaryAlgorithm *mafDataSet::boundaryAlgorithm() const {
    return m_DataBoundaryAlgorithm;
}


inline QString mafDataSet::boundaryAlgorithmName() const {
    return m_DataBoundaryAlgorithmName;
}

inline QString mafDataSet::externalDataType() const {
  return m_ExternalDataType;
}

inline void mafDataSet::setExternalDataType(QString externaldataType) {
  m_ExternalDataType = externaldataType;
}

inline bool mafDataSet::dataLoaded() const {
    return m_DataLoaded;
}

inline QVariantList mafDataSet::bounds()  {
    return m_Bounds;
}


Q_DECLARE_METATYPE(QVariantList);

} //mafResources

#endif // MAFDATASET_H
