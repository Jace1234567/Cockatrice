#ifndef SERVER_PROTOCOLHANDLER_H
#define SERVER_PROTOCOLHANDLER_H

#include <QObject>
#include <QPair>
#include "server.h"
#include "protocol.h"
#include "protocol_items.h"

class Server_Player;
class Server_Card;
class ServerInfo_User;
class Server_Room;
class QTimer;

class CommandContainer;
class Command_Ping;
class Command_Login;
class Command_Message;
class Command_ListUsers;
class Command_GetGamesOfUser;
class Command_GetUserInfo;
class Command_AddToList;
class Command_RemoveFromList;
class Command_DeckList;
class Command_DeckNewDir;
class Command_DeckDelDir;
class Command_DeckDel;
class Command_DeckDownload;
class Command_DeckUpload;
class Command_ListRooms;
class Command_JoinRoom;
class Command_LeaveRoom;
class Command_RoomSay;
class Command_CreateGame;
class Command_JoinGame;

class Command_KickFromGame;
class Command_LeaveGame;
class Command_GameSay;
class Command_Shuffle;
class Command_Mulligan;
class Command_RollDie;
class Command_DrawCards;
class Command_UndoDraw;
class Command_FlipCard;
class Command_AttachCard;
class Command_CreateToken;
class Command_CreateArrow;
class Command_DeleteArrow;
class Command_SetCardAttr;
class Command_SetCardCounter;
class Command_IncCardCounter;
class Command_ReadyStart;
class Command_Concede;
class Command_IncCounter;
class Command_CreateCounter;
class Command_SetCounter;
class Command_DelCounter;
class Command_NextTurn;
class Command_SetActivePhase;
class Command_DumpZone;
class Command_StopDumpZone;
class Command_RevealCards;
class Command_MoveCard;
class Command_SetSideboardPlan;
class Command_DeckSelect;

class Command_BanFromServer;
class Command_UpdateServerMessage;
class Command_ShutdownServer;

class Server_ProtocolHandler : public QObject {
	Q_OBJECT
protected:
	Server *server;
	QMap<int, QPair<Server_Game *, Server_Player *> > games;
	QMap<int, Server_Room *> rooms;

	Server *getServer() const { return server; }
	QPair<Server_Game *, Server_Player *> getGame(int gameId) const;

	AuthenticationResult authState;
	bool acceptsUserListChanges;
	bool acceptsRoomListChanges;
	ServerInfo_User *userInfo;
	QMap<QString, ServerInfo_User *> buddyList, ignoreList;
	
	void prepareDestroy();
	virtual bool getCompressionSupport() const = 0;
	int sessionId;
private:
	QList<ProtocolItem *> itemQueue;
	QList<int> messageSizeOverTime, messageCountOverTime;
	int timeRunning, lastDataReceived;
	QTimer *pingClock;

	virtual DeckList *getDeckFromDatabase(int deckId) = 0;

	ResponseCode cmdPing(const Command_Ping &cmd);
	ResponseCode cmdLogin(const Command_Login &cmd, BlaContainer *bla);
	ResponseCode cmdMessage(const Command_Message &cmd, BlaContainer *bla);
	virtual ResponseCode cmdAddToList(const Command_AddToList &cmd, BlaContainer *bla) = 0;
	virtual ResponseCode cmdRemoveFromList(const Command_RemoveFromList &cmd, BlaContainer *bla) = 0;
	virtual ResponseCode cmdDeckList(const Command_DeckList &cmd, BlaContainer *bla) = 0;
	virtual ResponseCode cmdDeckNewDir(const Command_DeckNewDir &cmd, BlaContainer *bla) = 0;
	virtual ResponseCode cmdDeckDelDir(const Command_DeckDelDir &cmd, BlaContainer *bla) = 0;
	virtual ResponseCode cmdDeckDel(const Command_DeckDel &cmd, BlaContainer *bla) = 0;
	virtual ResponseCode cmdDeckUpload(const Command_DeckUpload &cmd, BlaContainer *bla) = 0;
	virtual ResponseCode cmdDeckDownload(const Command_DeckDownload &cmd, BlaContainer *bla) = 0;
	ResponseCode cmdGetGamesOfUser(const Command_GetGamesOfUser &cmd, BlaContainer *bla);
	ResponseCode cmdGetUserInfo(const Command_GetUserInfo &cmd, BlaContainer *bla);
	ResponseCode cmdListRooms(const Command_ListRooms &cmd, BlaContainer *bla);
	ResponseCode cmdJoinRoom(const Command_JoinRoom &cmd, BlaContainer *bla);
	ResponseCode cmdListUsers(const Command_ListUsers &cmd, BlaContainer *bla);
	ResponseCode cmdLeaveRoom(const Command_LeaveRoom &cmd, Server_Room *room);
	ResponseCode cmdRoomSay(const Command_RoomSay &cmd, Server_Room *room);
	ResponseCode cmdCreateGame(const Command_CreateGame &cmd, Server_Room *room);
	ResponseCode cmdJoinGame(const Command_JoinGame &cmd, Server_Room *room);
	ResponseCode cmdLeaveGame(const Command_LeaveGame &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdKickFromGame(const Command_KickFromGame &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdConcede(const Command_Concede &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdReadyStart(const Command_ReadyStart &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdDeckSelect(const Command_DeckSelect &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdSetSideboardPlan(const Command_SetSideboardPlan &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdGameSay(const Command_GameSay &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdShuffle(const Command_Shuffle &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdMulligan(const Command_Mulligan &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdRollDie(const Command_RollDie &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdDrawCards(const Command_DrawCards &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdUndoDraw(const Command_UndoDraw &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdMoveCard(const Command_MoveCard &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdFlipCard(const Command_FlipCard &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdAttachCard(const Command_AttachCard &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdCreateToken(const Command_CreateToken &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdCreateArrow(const Command_CreateArrow &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdDeleteArrow(const Command_DeleteArrow &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdSetCardAttr(const Command_SetCardAttr &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdSetCardCounter(const Command_SetCardCounter &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdIncCardCounter(const Command_IncCardCounter &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdIncCounter(const Command_IncCounter &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdCreateCounter(const Command_CreateCounter &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdSetCounter(const Command_SetCounter &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdDelCounter(const Command_DelCounter &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdNextTurn(const Command_NextTurn &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdSetActivePhase(const Command_SetActivePhase &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdDumpZone(const Command_DumpZone &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdStopDumpZone(const Command_StopDumpZone &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	ResponseCode cmdRevealCards(const Command_RevealCards &cmd, Server_Game *game, Server_Player *player, BlaContainer *bla);
	virtual ResponseCode cmdBanFromServer(const Command_BanFromServer &cmd, BlaContainer *bla) = 0;
	virtual ResponseCode cmdShutdownServer(const Command_ShutdownServer &cmd, BlaContainer *bla) = 0;
	virtual ResponseCode cmdUpdateServerMessage(const Command_UpdateServerMessage &cmd, BlaContainer *bla) = 0;
	
	ResponseCode processSessionCommandContainer(const CommandContainer &cont, BlaContainer *bla);
	ResponseCode processRoomCommandContainer(const CommandContainer &cont, BlaContainer *bla);
	ResponseCode processGameCommandContainer(const CommandContainer &cont, BlaContainer *bla);
	ResponseCode processModeratorCommandContainer(const CommandContainer &cont, BlaContainer *bla);
	ResponseCode processAdminCommandContainer(const CommandContainer &cont, BlaContainer *bla);
private slots:
	void pingClockTimeout();
public:
	QMutex gameListMutex;
	
	Server_ProtocolHandler(Server *_server, QObject *parent = 0);
	~Server_ProtocolHandler();
	void playerRemovedFromGame(Server_Game *game);
	
	bool getAcceptsUserListChanges() const { return acceptsUserListChanges; }
	bool getAcceptsRoomListChanges() const { return acceptsRoomListChanges; }
	ServerInfo_User *getUserInfo() const { return userInfo; }
	virtual QString getAddress() const = 0;
	void setUserInfo(ServerInfo_User *_userInfo) { userInfo = _userInfo; }
	const QMap<QString, ServerInfo_User *> &getBuddyList() const { return buddyList; }
	const QMap<QString, ServerInfo_User *> &getIgnoreList() const { return ignoreList; }
	int getSessionId() const { return sessionId; }
	void setSessionId(int _sessionId) { sessionId = _sessionId; }

	int getLastCommandTime() const { return timeRunning - lastDataReceived; }
	void processCommandContainer(const CommandContainer &cont);
	virtual void sendProtocolItem(ProtocolItem *item, bool deleteItem = true) = 0;
	void enqueueProtocolItem(ProtocolItem *item);
};

#endif
