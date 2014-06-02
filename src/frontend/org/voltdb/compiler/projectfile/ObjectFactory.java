//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, vJAXB 2.1.10 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2012.07.11 at 03:04:20 PM EDT 
//


package org.voltdb.compiler.projectfile;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the org.voltdb.compiler.projectfile package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _Project_QNAME = new QName("", "project");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: org.voltdb.compiler.projectfile
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link VerticalpartitionsType.Verticalpartition }
     * 
     */
    public VerticalpartitionsType.Verticalpartition createVerticalpartitionsTypeVerticalpartition() {
        return new VerticalpartitionsType.Verticalpartition();
    }

    /**
     * Create an instance of {@link ProceduresType.Procedure }
     * 
     */
    public ProceduresType.Procedure createProceduresTypeProcedure() {
        return new ProceduresType.Procedure();
    }

    /**
     * Create an instance of {@link EvictablesType.Evictable }
     * 
     */
    public EvictablesType.Evictable createEvictablesTypeEvictable() {
        return new EvictablesType.Evictable();
    }

    /**
     * Create an instance of {@link UsersType.User }
     * 
     */
    public UsersType.User createUsersTypeUser() {
        return new UsersType.User();
    }

    /**
     * Create an instance of {@link SecurityType }
     * 
     */
    public SecurityType createSecurityType() {
        return new SecurityType();
    }

    /**
     * Create an instance of {@link ProceduresType }
     * 
     */
    public ProceduresType createProceduresType() {
        return new ProceduresType();
    }

    /**
     * Create an instance of {@link ExportsType.Connector.Tables.Table }
     * 
     */
    public ExportsType.Connector.Tables.Table createExportsTypeConnectorTablesTable() {
        return new ExportsType.Connector.Tables.Table();
    }

    /**
     * Create an instance of {@link ExportsType }
     * 
     */
    public ExportsType createExportsType() {
        return new ExportsType();
    }

    /**
     * Create an instance of {@link EvictablesType }
     * 
     */
    public EvictablesType createEvictablesType() {
        return new EvictablesType();
    }

    /**
     * Create an instance of {@link ClassdependenciesType }
     * 
     */
    public ClassdependenciesType createClassdependenciesType() {
        return new ClassdependenciesType();
    }

    /**
     * Create an instance of {@link SnapshotType }
     * 
     */
    public SnapshotType createSnapshotType() {
        return new SnapshotType();
    }

    /**
     * Create an instance of {@link PartitionsType }
     * 
     */
    public PartitionsType createPartitionsType() {
        return new PartitionsType();
    }

    /**
     * Create an instance of {@link SchemasType }
     * 
     */
    public SchemasType createSchemasType() {
        return new SchemasType();
    }

    /**
     * Create an instance of {@link ExportsType.Connector.Tables }
     * 
     */
    public ExportsType.Connector.Tables createExportsTypeConnectorTables() {
        return new ExportsType.Connector.Tables();
    }

    /**
     * Create an instance of {@link ExportsType.Connector }
     * 
     */
    public ExportsType.Connector createExportsTypeConnector() {
        return new ExportsType.Connector();
    }

    /**
     * Create an instance of {@link PartitionsType.Partition }
     * 
     */
    public PartitionsType.Partition createPartitionsTypePartition() {
        return new PartitionsType.Partition();
    }

    /**
     * Create an instance of {@link SchemasType.Schema }
     * 
     */
    public SchemasType.Schema createSchemasTypeSchema() {
        return new SchemasType.Schema();
    }

    /**
     * Create an instance of {@link GroupsType.Group }
     * 
     */
    public GroupsType.Group createGroupsTypeGroup() {
        return new GroupsType.Group();
    }

    /**
     * Create an instance of {@link VerticalpartitionsType }
     * 
     */
    public VerticalpartitionsType createVerticalpartitionsType() {
        return new VerticalpartitionsType();
    }

    /**
     * Create an instance of {@link UsersType }
     * 
     */
    public UsersType createUsersType() {
        return new UsersType();
    }

    /**
     * Create an instance of {@link ClassdependenciesType.Classdependency }
     * 
     */
    public ClassdependenciesType.Classdependency createClassdependenciesTypeClassdependency() {
        return new ClassdependenciesType.Classdependency();
    }

    /**
     * Create an instance of {@link DatabaseType }
     * 
     */
    public DatabaseType createDatabaseType() {
        return new DatabaseType();
    }

    /**
     * Create an instance of {@link GroupsType }
     * 
     */
    public GroupsType createGroupsType() {
        return new GroupsType();
    }

    /**
     * Create an instance of {@link ProjectType }
     * 
     */
    public ProjectType createProjectType() {
        return new ProjectType();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ProjectType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "", name = "project")
    public JAXBElement<ProjectType> createProject(ProjectType value) {
        return new JAXBElement<ProjectType>(_Project_QNAME, ProjectType.class, null, value);
    }

}
