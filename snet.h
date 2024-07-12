/*
 * Copyright (c) 1995,2001 Regents of The University of Michigan.
 * All Rights Reserved.  See COPYRIGHT.
 */

typedef struct {
    int			sn_fd;
    char		*sn_rbuf;
    int			sn_rbuflen;
    char		*sn_rend;
    char		*sn_rcur;
    int			sn_maxlen;
    int			sn_rstate;
    char		*sn_wbuf;
    int			sn_wbuflen;
    int			sn_flag;
    struct timeval	sn_read_timeout;
    struct timeval	sn_write_timeout;

#ifdef HAVE_ZLIB
    z_stream		sn_zistream;
    z_stream		sn_zostream;
    char		*sn_zbuf;
    int			sn_zbuflen;
#endif /* HAVE_ZLIB */

#ifdef HAVE_LIBSSL
    void		*sn_ssl;
#endif /* HAVE_LIBSSL */

#ifdef HAVE_LIBSASL
    sasl_conn_t		*sn_conn;
    int			sn_saslssf;
    unsigned int	sn_saslmaxout;
#endif /* HAVE_LIBSASL */
} SNET;

#define SNET_EOF		(1<<0)
#define SNET_TLS		(1<<1)
#ifdef HAVE_LIBSASL
#define SNET_SASL		(1<<2)
#endif /* HAVE_LIBSASL */
#define SNET_WRITE_TIMEOUT	(1<<3)
#define SNET_READ_TIMEOUT	(1<<4)

#define SNET_ZLIB		(1<<5)

#define snet_fd( sn )	((sn)->sn_fd)
#define snet_saslssf( sn )	((sn)->sn_saslssf)
#define snet_flags( sn )	((sn)->sn_flag)
#define snet_zistream( sn )	((sn)->sn_zistream)
#define snet_zostream( sn )	((sn)->sn_zostream)

#define snet_writef( sn, ... )	snet_writeftv((sn),NULL, __VA_ARGS__ )

int	snet_eof( SNET * );
SNET	*snet_attach( int, int );
SNET	*snet_open( char *, int, int, int );
int	snet_close( SNET * );
ssize_t	snet_writeftv( SNET *, struct timeval *, char *, ... );
char	*snet_getline( SNET *, struct timeval * );
char	*snet_getline_multi( SNET *, void (*)(char *),
		struct timeval * );
void	snet_timeout( SNET *, int, struct timeval * );
int	snet_hasdata( SNET * );
ssize_t	snet_read( SNET *, char *, size_t, struct timeval * );
ssize_t	snet_write( SNET *, char *, size_t, struct timeval * );
int	snet_setcompression( SNET *, int, int );
#ifdef HAVE_LIBSSL
int	snet_starttls( SNET *, SSL_CTX *, int );
#endif
#ifdef HAVE_LIBSASL
int	snet_setsasl ( SNET *, sasl_conn_t * );
#endif
