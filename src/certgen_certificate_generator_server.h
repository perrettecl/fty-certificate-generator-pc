/*  =========================================================================
    certgen_certificate_generator_server - class description

    Copyright (C) 2014 - 2019 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#ifndef CERTGEN_CERTIFICATE_GENERATOR_SERVER_H_INCLUDED
#define CERTGEN_CERTIFICATE_GENERATOR_SERVER_H_INCLUDED

#include <fty_common_sync_server.h>
#include <functional>
#include <memory>

namespace certgen
{
    using Command   = std::string;

    using FctCommandHandler = std::function<std::string (const std::vector<std::string> &)>;

    class CertificateGeneratorServer final : public fty::SyncServer
    {
        public:
            explicit CertificateGeneratorServer(const std::string & configPath);
            fty::Payload handleRequest(const fty::Sender & sender, const fty::Payload & payload) override;

        private: // methods
            // List of supported commands with a reference to the handler for this command.
            std::string m_configPath;
            
            std::map<Command, FctCommandHandler> m_supportedCommands;
            std::map<std::string, std::pair<fty::Keys, fty::CsrX509>> m_csrPending; // needed to import an existing certificate correctly 

            // Handlers for all supported commands
            std::string handleGenerateSelfsignedCertificate(const fty::Payload & params);
            std::string handleGenerateCSR(const fty::Payload & params);
            std::string handleImportCertificate(const fty::Payload & params);
            std::string handleGetPendingCSR(const fty::Payload & params);
            std::string handleRemovePendingCSR(const fty::Payload & params);
    };

} // namescpace certgen


void certgen_certificate_generator_server_test (bool verbose);

#endif
