/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2009 The EVEmu Team
    For the latest information visit http://evemu.mmoforge.org
    ------------------------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any later
    version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place - Suite 330, Boston, MA 02111-1307, USA, or go to
    http://www.gnu.org/copyleft/lesser.txt.
    ------------------------------------------------------------------------------------
    Author:     Captnoord
*/

#ifndef __SPACE_H
#define __SPACE_H


typedef std::list<EveClientSession*>                        SessionList;
typedef SessionList::iterator                               SessionListItr;
typedef SessionList::const_iterator                         SessionListConstItr;

typedef std::set<EveClientSession*>                         SessionSet;
typedef SessionSet::iterator                                SessionSetItr;
typedef SessionSet::const_iterator                          SessionSetConstItr;

typedef std::tr1::unordered_map<uint32, EveClientSession*>  SessionMap;
typedef SessionMap::iterator                                SessionMapItr;
typedef SessionMap::const_iterator                          SessionMapConstItr;

// keep track of the space info stuff related to this server
class SERVER_DECL Space : public Singleton<Space>
{
public:
    Space();

    // ---- space information ----
    bool Load_SpaceForm_fromDB(Database *targetdb);
    void Delete_SpaceForm();
    bool Create_RegionManagers_fromDB(Database *targetdb);
    void Delete_RegionManagers();

    // ---------------------------

    size_t GetConnectionCount() { return mAcceptedConnections; }
    size_t GetAuthorizedCount() { return mAuthorizedConnections; }

    /* update server stuff not related to sessions */
    void Update(time_t diff);

    /* update sessions and dispatch the queued packets */
    void UpdateSessions(time_t diff);

    EveClientSession* FindSession(uint32 userid);
    EveClientSession* FindSessionByName(const char *);

    void AddSession(EveClientSession *);
    void RemoveSession(uint32 userid);

    void AddGlobalSession(EveClientSession *session);
    void RemoveGlobalSession(EveClientSession *session);
    void DeleteSession(EveClientSession *session);

    ASCENT_INLINE size_t GetSessionCount() const { return m_sessions.size(); }

    //void SetMotd(const char *motd) { m_motd = motd; }
    //ASCENT_INLINE const char* GetMotd() const { return m_motd.c_str(); }

    ASCENT_INLINE time_t GetGameTime() const { return m_gameTime; }

    ASCENT_INLINE void SetStartTime(uint32 val) { mStartTime = val; }
    ASCENT_INLINE uint32 GetUptime(void) { return (uint32)UNIXTIME - mStartTime; }
    ASCENT_INLINE uint32 GetStartTime(void) { return mStartTime; }
    std::string GetUptimeString();

    /**
    * @brief OnClientDisconnect is triggered when a socket is disconnected from the server.
    *
    * no long description.
    *
    * @note this function is purely for server statistics.
    */
    void OnClientDisconnect();

    /**
    * @brief OnClientConnect is triggered when a client is authorized successfully.
    *
    * no long description.
    *
    * @note this function is purely for server statistics.
    */
    void OnClientConnect();
    /**
     * @brief a function to generate user id's.
     *
     * no long description.
     *
     * @return a freshly generated userid.
     * @note this is so fucked up.... lol..... I hope that because of its natural overrun it will be safe.... lol.... but it isn't safe... (for clients hehe)
     */
    uint32 GenerateUserId() { return mUserIdGeneratorNumber++; }

    uint32 GetProxyNodeID(){return mProxyNodeID;}

private:

    // space information
    uint32 m_regionsSize;
    Region *m_regions;

    uint32 m_constellationsSize;
    Constellation *m_constellations;
    //------------------

    // region managers objects got from DB assigned by is ID.
    //uint32 m_regionSize;
    //RegionMapMgr *m_spaceRegionsMgrs;
    //------------------

    SessionMap m_sessions;
    RWLock m_sessionlock;

protected:
    size_t mAcceptedConnections;
    size_t mAuthorizedConnections;

    uint32 mUserIdGeneratorNumber;

    uint32 mStartTime;
    uint32 mProxyNodeID;
    uint32 m_queueUpdateTimer;

    Mutex SessionsMutex;//FOR GLOBAL !
    SessionSet Sessions;

    time_t m_gameTime;
    time_t m_lastTick;
    uint32 TimeOut;
};


#endif//__SPACE_H

#define sSpace Space::getSingleton()
