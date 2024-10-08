/*
 * Copyright 2016 Red Hat, Inc. and/or its affiliates
 * and other contributors as indicated by the @author tags.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.keycloak.adapters.undertow;

import io.undertow.server.HttpServerExchange;
import io.undertow.util.AttachmentKey;
import org.keycloak.KeycloakSecurityContext;
import org.keycloak.adapters.OIDCHttpFacade;
import org.keycloak.adapters.undertow.UndertowHttpFacade;

/**
 * @author <a href="mailto:bill@burkecentral.com">Bill Burke</a>
 * @version $Revision: 1 $
 */
public class OIDCUndertowHttpFacade extends UndertowHttpFacade implements OIDCHttpFacade {
    public static final AttachmentKey<KeycloakSecurityContext> KEYCLOAK_SECURITY_CONTEXT_KEY = AttachmentKey.create(KeycloakSecurityContext.class);

    public OIDCUndertowHttpFacade(HttpServerExchange exchange) {
        super(exchange);
    }

    @Override
    public KeycloakSecurityContext getSecurityContext() {
        return exchange.getAttachment(KEYCLOAK_SECURITY_CONTEXT_KEY);
    }

}
